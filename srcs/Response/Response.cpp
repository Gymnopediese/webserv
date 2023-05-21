/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:38:59 by albaud            #+#    #+#             */
/*   Updated: 2023/05/20 10:26:11 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(void){}
Response::Response(int status, string status_message, string content_type, vector<string> header, string content)
: status(status), status_message(status_message), content_type(content_type), content(content)
{
	(void) header;
}
Response::~Response(){}
string	Response::str(void)
{
	stringstream res;

	res << "HTTP/1.1  " << status << " " << status_message << "\r\n";
	res << "Content-Type: " << content_type << "\r\n";
	res << "Content-Length: " << content.size() << "\r\n";
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
