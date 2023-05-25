/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:23:44 by albaud            #+#    #+#             */
/*   Updated: 2023/05/25 00:56:33 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.hpp"

#define VITER(type, variable) for (vector<type>::iterator val = variable.begin(); val < variable.end(); val++)

void Request::get_cookies()
{
	string 			cook;
	vector<string>	vars;
	vector<string>	var;

	cook = headers["Cookie"];
	if (cook == "")
		return ;
	vars = split(cook, "; ");
	for (int i = 0; i < (int)vars.size(); i++)
	{
		var = split(vars[i], "=");
		cookie[var[0]] = var[1];
	}
}

void Request::get_post()
{
	int i;
	cout << "lines" << endl;
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
			cout << temp[ind] << endl;
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

void Request::get_headers()
{
	string		res = "";
	char		b[1024 + 1];
	int			size;
	
	errno = 0;
	size = 1;
	while (size)
	{
		size = recv(fd, b, 1024, 0);
		if (size <= 0)
		{
			perror("retars");
			break;
		}
		b[size] = 0;
        res.append(b, size);
		if (res.find("\r\n\r\n") >= 0)
		{
			std::pair<string, string> pair = split2(res, "\r\n\r\n");
			header = pair.first;
			content = pair.second;
			return ;
		}
	}
	error("invalid request");
	return ;
}

int get_divider(long long int s)
{
	int	n = 0;
	while (s / ++n > 10480);
	return (n);
}

void Request::get_body(long long int s)
{
	if (s - content.length() < 0)
		error("413 mes gross couilles");
	s -= content.length();
	int				n = get_divider(s);
	string			res = "";
	char			b[s / n + 1];
	int				size = 1;
	long long int	r = 0;

	r = 0;
	while (1)
	{
		if (r > s)
			error("413 mes gross couilles");
		size = recv(fd, b, s / n, 0);
		if (size <= 0)
		{
			perror("no body");
			if (type == "POST")
				get_post();
			return ;
		}
		b[size] = 0;
        res.append(header, size);
	}
}

void	Request::add_headers(vector<string> lines)
{
	std::pair<string, string> pair;
	for (size_t i = 1; i < lines.size(); i++)
	{
		pair = split2(lines[i], ": ");
		if (pair.first != "")
			headers[pair.first] = pair.second;
		else
			error("invalid headers");
	}
}

Request::Request(int fd) : fd(fd)
{
	get_headers();
	std::pair<string, string> pair;
	vector<string> lignes = split(header, "\r\n");
	vector<string> key_pair = split(lignes[0], " ");
	
	type = key_pair[0];
	strtolower(type);
	http_version = key_pair[2];
	file = key_pair[1];
	uri = key_pair[1];
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
	get_cookies();

	cout << header << endl;
	if (type == "POST")
	{
		content_type = split2(headers["Content-Type"], ";").first;
	}
}

Request::Request(void){}
Request::~Request(){}