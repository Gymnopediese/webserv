/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:38:59 by albaud            #+#    #+#             */
/*   Updated: 2023/05/25 11:10:20 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(void){}


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
			Response r = Response(408, *conf);
			r.late.client = late.client;
			*this = r;
			return (true);
		}
		return (false);
	}
	char buffer[10000];
	ssize_t bytesRead = read(late.fd, buffer, 10000 - 1);
	buffer[bytesRead] = 0;
	close(late.fd);
	content = string(buffer);

	if ((int)content.find("\r\n\r\n") == -1)
	{
		return (true);
	}
	string h = split2(content, "\r\n\r\n").first;
	content = split2(content, "\r\n\r\n").second;
	vector <string> t = split(h, "\r\n");
	header.insert(header.end(), t.begin(), t.end());
	for (size_t i= 0; i < header.size(); i++)
	{
		if ((int)header[i].find("Location: ") == -1)
			continue;
		status = 302;
		status_message = "302 Found";
		break ;
	}
	return (true);
}

map<int, string>	default_errorpage()
{
	map<int, string> res;

	res[400] = "400 Bad Request";
	res[404] = "404 Not Found";
	res[405] = "405 Method Not Allowed";
	res[408] = "408 Request Timeout";
	res[410] = "410 Gone";
	res[411] = "411 Length Required";
	res[413] = "413 Payload Too Large";
	res[414] = "414 URI Too Long";
	res[418] = "418 I'm a teapot";
	res[421] = "421 Misdirected Request";
	res[422] = "422 Unprocessable Entity";
	return (res);
}

map<int, string>	get_map()
{
	map<int, string> res;

	res[200] = "200 OK";
	res[201] = "201 Created";

	res[302] = "302 Found";

	res[400] = "400 Bad Request";
	res[404] = "404 Not Found";
	res[405] = "405 Method Not Allowed";
	res[408] = "408 Request Timeout";
	res[410] = "410 Gone";
	res[411] = "411 Length Required";
	res[413] = "413 Payload Too Large";
	res[414] = "414 URI Too Long";
	res[418] = "418 I'm a teapot";
	res[421] = "421 Misdirected Request";
	res[422] = "422 Unprocessable Entity";


	res[508] = "508 Loop Detected";
	return (res);
}

Response::Response(int status, Config &conf, string location)
{
	this->conf = &conf;
	late.waiting = false;
	this->status = status;
	status_message = get_map()[status];
	if (status >= 400 && status <= 499)
	{
		if (conf.error_pages.find(status) == conf.error_pages.end() || !file_exist(conf.error_pages[status]))
			content = file_to_str(default_errorpage()[status]);
		else
			content = conf.error_pages[status];
	}
	if (status == 302)
	{
		header.push_back("Location: " + location);
	}
}
Response::~Response(){}
string	Response::str(void)
{
	stringstream res;


	cout << "NANI " << content.length()  << ":" << content << endl;
	res << "HTTP/1.1  " << status_message << "\r\n";
	res << "Content-Type: text/html\r\n";
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
