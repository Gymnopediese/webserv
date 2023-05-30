/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:14:50 by albaud            #+#    #+#             */
/*   Updated: 2023/05/29 11:57:23 by albaud           ###   ########.fr       */
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

public:

	size_t				start_time;
	bool				header_done;
	bool				chunked;
	string				content;
	size_t				content_length;
	string				content_type;

	string				http_version;
	string				path_info;
	string				global_path_info;

	string				boundary;
	map<string, string>	headers;
	string				header;
	int					fd;
	string				uri;
	string				query;
	string				file;
	string				file_extention;
	string				type;
	string				port;
	string				host;
	vector<t_post>		post;
	long long int		client_max_body_size;
	Request(void);
	bool				recv(int fd);
	bool				get_body(int fd, long long int s);
	void				get_post();
	void				message(int fd);
	void				add_headers(vector<string> lines);
	void				parse_request();
	~Request();
};
#endif