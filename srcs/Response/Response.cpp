/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:38:59 by albaud            #+#    #+#             */
/*   Updated: 2023/05/30 08:27:09 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(void): status(0){
	late.waiting = false;
}

Response& Response::operator=(const Response &copy)
{
	conf = copy.conf;
	late = copy.late;
	status = copy.status;
	status_message = copy.status_message;
	content_type = copy.content_type;
	content = copy.content;
	header = copy.header;
	cookie = copy.cookie;
	return (*this);
}

bool Response::get_late_content()	
{
	int	status;

	if (late.waiting == false)
		return true;
	if (waitpid(late.pid, &status, WNOHANG) <= 0)
	{
		if (get_time() - late.start > 10000000)
		{
			kill(late.pid, SIGQUIT);
			throw 508;
		}
		return (false);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		cout << "error is a nigga" << endl;
		throw 575;
	}
	char buffer[2049];
	content = "";

	ssize_t bytesRead = 1;
	while (bytesRead)
	{
		bytesRead = read(late.fd, buffer, 2048);
		if (bytesRead < 0)
			throw 500;
		content.append(buffer, bytesRead);
	}
	if ((int)content.find("\r\n\r\n") == -1)
	{
		content = str();
		return (true);
	}
	string h = split2(content, "\r\n\r\n").first;
	content = split2(content, "\r\n\r\n").second;
	vector <string> t = split(h, "\r\n");
	header.insert(header.end(), t.begin(), t.end());
	for (size_t i= 0; i < header.size(); i++)
	{
		if ((int)header[i].find("Location: ") == -1)
			continue ;
		status = 302;
		status_message = "302 Found";
		break ;
	}
	content = str();
	return (true);
}


map<int, string>	get_map()
{
	map<int, string> res;

	res[200] = "200 OK";
	res[201] = "201 Created";

	res[302] = "302 Found";

	res[400] = "400 Bad Request";
	res[403] = "403 Forbidden";					//cannot open file
	res[404] = "404 Not Found";					//no thingus \r\n\r\n finds after 10seconds
	res[405] = "405 Method Not Allowed";		//when request unavalable method
	res[408] = "408 Request Timeout";
	//res[410] = "410 Gone";
	res[411] = "411 Length Required";
	res[413] = "413 Payload Too Large";			//body too large
	res[414] = "414 URI Too Long";				//
	res[415] = "415 Unsupported Media Type";	// mmmmmmmmmmmmmmm
	res[418] = "418 I'm a teapot";					// if request type is teapot
	res[421] = "421 Misdirected Request";			//localhost not set
	res[422] = "422 Unprocessable Entity";			//szntax error
	res[431] = "431 Request Header Fields Too Large";

	
	res[500] = "500 Internal Server Error";			//CGI IGUESS
	res[501] = "501 Not Implemented";				//while loops in cgi
	res[505] = "505 HTTP Version Not Supported";	//while loops in cgi
	res[508] = "508 Loop Detected";					//while loops in cgi
	res[575] = "575 CGI Error";
	return (res);
}

Response::Response(int status, Config *conf, string location)
{
	this->conf = conf;
	late.waiting = false;
	this->status = status;
	late.waiting = false;
	status_message = get_map()[status];
	if (status >= 400 && status <= 599)
	{
		if (conf == 0)
			content = file_to_str("./default/" + to_string(status) + ".html");
		else
		{
			string file = conf->root + conf->error_pages[status];
			if (conf->error_pages.find(status) == conf->error_pages.end() || !file_exist(file))
				content = file_to_str("./default/" + to_string(status) + ".html");
			else
				content = file_to_str(file);
		}
	}
	if (status == 302)
	{
		header.push_back("Location: " + location);
	}
}

string	get_date()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer [200];

	time (&rawtime);
	timeinfo = localtime (&rawtime);
	strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %Z", timeinfo);
	return (string(buffer));
}

Response::~Response(){}


void	Response::message(int fd)
{
	string color;

	if (status < 300)
		color = GREEN;
	else if (status < 400)
		color = BLUE;
	else
		color = RED;
	harl(INFOS,  color + "[Response to "  + to_string(fd) + "] " + status_message + RESET, color);
}

string	Response::str(void)
{
	stringstream res;

	res << "HTTP/1.1  " << status_message << "\r\n";
	res << "Date: " << get_date() << "\r\n";
	if (content_type != "")
		res << "Content-Type: " << content_type << "\r\n";
	res << "Content-Length: " << content.length() << "\r\n";
	for (vector<string>::iterator i = header.begin(); i != header.end(); i++)
	{
		res << *i << "\r\n";
	}
	res << "\r\n";
	res << content;
	return (res.str());
}

// // PAGE NOT FOUND
// std::string error404()
// {
// 	string response;

// 	string html = file_to_str("conf/404.html");
// 	response += "HTTP/1.1 404 Not Found\r\n";
//     response += "Content-Type: text/html\r\n";
//     response += "Content-Length: " + to_string(html.length())+ "\r\n";
//     response += "\r\n";
//     response += html;
// 	return response;
// }

// // METHOD NOT ALLOWED
// std::string error405()
// {
// 	stringstream response;
// 	response << "HTTP/1.1 405 Method Not Allowed\r\n";
// 	response << "Allow: GET, POST\r\n";
// 	response << "Content-Type: text/plain\r\n";
// 	response << "Content-Length: 44\r\n";
// 	response << "La méthode DELETE n'est pas autorisée pour cette ressource.\r\n";
// 	response << "\r\n";
// 	return response.str();
// }

// string flavicon(string icon)
// {
// 	stringstream response;
// 	response << "HTTP/1.1 200 OK\r\n";
// 	response << "Content-Type: image/x-icon\r\n";
// 	response << "Content-Length: " << icon.length() << "\r\n";
// 	response << "Cache-Control: max-age=86400\r\n";
// 	response << "\r\n";
// 	response << icon;
// 	return response.str();
// }

// string ok200(string html)
// {
// 	stringstream response;
//     response << "HTTP/1.1 200 OK\r\n";
//     response << "Content-Type: text/html\r\n";
//     response << "Content-Length: " << html.length() << "\r\n";
//     response << "\r\n";
//     response << html;
// 	return (response.str());
// }
