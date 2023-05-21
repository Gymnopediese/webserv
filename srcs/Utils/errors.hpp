/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:02:34 by albaud            #+#    #+#             */
/*   Updated: 2023/05/19 19:57:44 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_HPP
#define ERRORS_HPP

#include "../header.hpp"

// Informational 1xx
#define HTTP_CONTINUE 100          // Used to continue the request

// Success 2xx
#define HTTP_OK 200                // The request was successful
#define HTTP_CREATED 201           // The request has been fulfilled, resulting in the creation of a new resource
#define HTTP_ACCEPTED 202          // The request has been accepted for processing, but the processing has not been completed
#define HTTP_NO_CONTENT 204        // The server successfully processed the request but doesn't need to return a response

// Redirection 3xx
#define HTTP_MOVED_PERMANENTLY 301 // The requested resource has been assigned a new permanent URI
#define HTTP_FOUND 302             // The requested resource resides temporarily under a different URI
#define HTTP_NOT_MODIFIED 304      // Indicates that the resource has not been modified since the version specified by the request headers

// Client Error 4xx
#define HTTP_BAD_REQUEST 400       // The server cannot or will not process the request due to a client error
#define HTTP_UNAUTHORIZED 401      // Authentication is required and has failed or has not been provided
#define HTTP_FORBIDDEN 403         // The server understood the request but refuses to authorize it
#define HTTP_NOT_FOUND 404         // The requested resource could not be found on the server

// Server Error 5xx
#define HTTP_INTERNAL_SERVER_ERROR 500  // A generic error message, typically when an unexpected condition was encountered
#define HTTP_NOT_IMPLEMENTED 501        // The server does not support the functionality required to fulfill the request
#define HTTP_BAD_GATEWAY 502            // The server was acting as a gateway or proxy and received an invalid response
#define HTTP_SERVICE_UNAVAILABLE 503    // The server is currently unable to handle the request

// Custom Defines
#define HTTP_CUSTOM_ERROR_1 550     // Custom error code 1
#define HTTP_CUSTOM_ERROR_2 551     // Custom error code 2

#endif


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
