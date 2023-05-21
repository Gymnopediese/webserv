/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:14:50 by albaud            #+#    #+#             */
/*   Updated: 2023/05/20 10:18:47 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "../header.hpp"

// definir comme ca les reponse error et normal
#define OK200(type, content) Response(200, "OK", type, vector<string>(), content)
#define FAVICON(content) Response(200, "OK", "image/x-icon", vector<string>(), content)


class Response
{
private:
	int					status;
	string				status_message;
	string				content_type;
	string				content;
	map<string, string>	header;
	map<string, string>	cookie;

public:

	Response(void);
	Response(int status, string status_message, string content_type, vector<string> header, string content);
	~Response();
	string	str(void);
};

#endif