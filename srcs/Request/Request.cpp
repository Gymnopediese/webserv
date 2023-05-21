/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:23:44 by albaud            #+#    #+#             */
/*   Updated: 2023/05/21 03:00:00 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.hpp"

#define VITER(type, variable) for (vector<type>::iterator val = variable.begin(); val < variable.end(); val++)

string	subfrom(string str, string sub)
{
	int		start;

	start = str.find(sub);
	if (start == -1)
		return ("");
	return (str.substr(start + sub.length()));
}

string	subfromto(string str, string sub, string subend)
{
	int		start;
	int		end;

	start = str.find(sub);
	end = str.find(subend, start + sub.length());
	if (start == -1 || end == -1)
		return ("");
	start += sub.length();
	return (str.substr(start, end - start));
}

void Request::get_cookies()
{
	string 			cook;
	vector<string>	vars;
	vector<string>	var;

	cook = header["Cookie"];
	if (cook == "")
		return ;
	vars = split(cook, "; ");
	for (int i = 0; i < (int)vars.size(); i++)
	{
		var = split(vars[i], "=");
		cookie[var[0]] = var[1];
	}
}

void Request::get_post(string &text)
{
	int i;
	cout << "lines" << endl;
	boundary = "--" + subfrom(header["Content-Type"], "boundary=");
	if (boundary == "--")
		return ;
	vector<string> lines = split(text, boundary);
	for (i = 1; i < (int)lines.size(); i++)
	{
		t_post post;
		vector<string> temp = split(lines[i], "\r\n");
		int ind = 0;
		printr(lines[i].substr(0, 500));
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

Request::Request(string request_text)
{
	int i;
	vector<string> lignes = split(request_text, "\r\n");
	vector<string> key_pair = split(lignes[0], " ");
	type = key_pair[0];
	file = key_pair[1];
	http_version = key_pair[2];
	file_extention = split(file, ".")[1];
	for (i = 1; i < (int)lignes.size(); i++)
	{
		key_pair = split(lignes[i], ": ");
		if (key_pair.size() == 2)
			header[key_pair[0]] = key_pair[1];
		else
			break;
	}
	key_pair = split(header["Host"], ":");
	host = key_pair[0];
	port = key_pair[1];
	if (type == "POST")
	{
		get_post(request_text);
	}
	get_cookies();
}

Request::Request(void){}
Request::~Request(){}