/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:14:50 by albaud            #+#    #+#             */
/*   Updated: 2023/05/25 10:43:05 by albaud           ###   ########.fr       */
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
	string				http_version;
	string				content;
	string				boundary;
	string				content_type;
	map<string, string>	headers;
	string				header;
	int					fd;
	string				uri;
	string				path_info;
	string				global_path_info;
	string				query;
	string				file;
	string				file_extention;
	string				type;
	string				port;
	string				host;
	vector<t_post>		post;
	map<string, string>	cookie;
	Request(void);
	Request(int fd);
	void	get_headers();
	void	get_body(long long int size);
	void	get_cookies();
	void	get_post();

	void	add_headers(vector<string> lines);

	~Request();
};
#endif