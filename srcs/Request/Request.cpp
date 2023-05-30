/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:23:44 by albaud            #+#    #+#             */
/*   Updated: 2023/05/30 08:21:53 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

#define VITER(type, variable) for (vector<type>::iterator val = variable.begin(); val < variable.end(); val++)

string unchunk(string content)
{
	vector<string> chunkes;
	string res = "";
	chunkes = split(content, "\r\n");
	for (size_t i = 0; i < chunkes.size(); i++)
	{
		if (i % 2)
			res += chunkes[i];
	}
	return (res);
}

void Request::get_post()
{
	if (chunked)
	{
		content = unchunk(content);
		content_length = content.size();
		return ;
	}
	int i;
	boundary = "--" + subfrom(headers["Content-Type"], "boundary=");
	if (boundary == "--")
		return ;
	vector<string> lines = split(content, boundary);
	for (i = 1; i < (int)lines.size(); i++)
	{
		t_post post;
		vector<string> temp = split(lines[i], "\r\n");
		int ind = 0;
		start:
		while (ind < (int)temp.size() && temp[ind] == "")
			ind++;
		if ((int)temp[ind].find("Content-Disposition:") != -1)
		{
			post.name = subfromto(temp[ind], "name=\"", "\"");
			post.filename = subfromto(temp[ind], "filename=\"", "\"");
			ind++;
			goto start; 
		}
		if ((int)temp[ind].find("Content-Type: ") != -1)
		{
			cout << temp[ind] << endl;
			post.content_type = subfrom(temp[ind], "Content-Type: ");
			ind++;
			goto start; 
		}
		while (ind < (int)temp.size() && temp[ind] == "")
			ind++;
		post.content = join(temp, ind, (int)temp.size() - 1, "\r\n");
		cout << "post.name\t\t" << post.name << endl;
		cout << "post.filename\t\t" << post.filename << endl;
		cout << "post.contentype\t" << post.content_type << endl;
		cout << "post.content\t\t" << post.content << endl;
		this->post.push_back(post);
	}
}

void	Request::message(int fd)
{
	string color;
	if (type == "post")
		color = MAGENTA;
	else if (type == "get")
		color = BLUE;
	else
		color = YELLOW;
	harl(INFOS, color + "[Request from " + to_string(fd) + "] " + strtoupper(type) + " " + uri + " " + to_string(content_length) + " " + http_version + RESET, color);
}

bool Request::recv(int fd)
{
	char		b[2048 + 1];
	int			size;

	size = ::recv(fd, b, 2048, MSG_DONTWAIT);
	if (size <= 0)
		throw size;
	if (header_done)
	{
		content.append(b, size);
		return (false);
	}
	header.append(b, size);
	if (header.size() > 15000)
	{
		cout << header.size() << endl;
		throw 431;
	}
	if ((int)header.find("\r\n\r\n") < 0)
		return (false);
	std::pair<string, string> pair = split2(header, "\r\n\r\n");
	header = pair.first;
	content = pair.second;
	parse_request();
	header_done = true;
	return (true);
}

int get_divider(long long int s)
{
	int	n = 0;
	while (s / ++n > 10480);
	return (n);
}

void	Request::add_headers(vector<string> lines)
{
	std::pair<string, string> pair;
	for (size_t i = 1; i < lines.size(); i++)
	{
		pair = split2(lines[i], ": ");
		if (pair.first != lines[i])
			headers[pair.first] = pair.second;
		else
			throw 422;
	}
}

void	Request::parse_request()
{
	std::pair<string, string> pair;
	vector<string> lignes = split(header, "\r\n");
	vector<string> key_pair = split(lignes[0], " ");
	if (key_pair.size() != 3)
		throw 422;
	content_length = 0;
	type = key_pair[0];
	strtolower(type);
	if (type == "teapots")
		throw 418;
	if (type != "post" && type != "get" && type != "delete")
		throw 501;
	http_version = key_pair[2];
	if (http_version != "HTTP/1.1")
		throw 505;
	file = key_pair[1];
	uri = key_pair[1];
	if (uri.length() >= 8190)
		throw 414;
	query = split2(uri, "?").second;
	uri = split2(uri, "?").first;
	file = uri;
	file_extention = "." + split2(file, ".").second;
	path_info = "/" + split2(file_extention, "/").second;
	file_extention = split2(file_extention, "/").first;
	uri = split2(file, ".").first;
	if (file_extention != ".")
		uri += file_extention;
	file = uri;
	add_headers(lignes);
	pair = split2(headers["Host"], ":");
	host = pair.first;
	port = pair.second;
	if (type != "post")
		return ;
	if (headers["Transfer-Encoding"] == "chunked")
		chunked = true;
	if (!chunked && headers.find("Content-Length") == headers.end())
		throw 411;
	if (!chunked)
		content_length = strtoll(headers["Content-Length"].c_str(), 0, 10);
	else
		content_length = -1;
}

Request::Request(void): start_time(get_time()), header_done(false), chunked(false), content_length(-1)
{

}
Request::~Request(){}