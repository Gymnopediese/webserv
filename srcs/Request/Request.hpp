/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:14:50 by albaud            #+#    #+#             */
/*   Updated: 2023/05/21 01:40:21 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REQUEST_HPP
#define REQUEST_HPP


#include "../header.hpp"

typedef struct s_post
{
	string 	name;
	string	filename;
	string	content_type;
	string	content;
}	t_post;

class Request
{
private:
	string			http_version;
	string			content;
	string			boundary;
	map<string, string>	header;

public:
	string			file;
	string			file_extention;
	string			type;
	string			port;
	string			host;
	vector<t_post>	post;
	map<string, string>	cookie;
	Request(void);
	Request(string request_text);
	void	get_cookies();
	void	get_post(string &text);
	~Request();
};
#endif