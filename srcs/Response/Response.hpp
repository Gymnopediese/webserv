/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:14:50 by albaud            #+#    #+#             */
/*   Updated: 2023/05/30 00:46:05 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "../header.hpp"
#include "../Config/Config.hpp"

typedef struct s_late
{
	long long 			start;
	int					pid;
	int					fd;
	int					client;
	bool				waiting;
}	t_late;

class Config;

class Response
{
private:
public:
	Config				*conf;
	t_late				late;
	int					status;
	string				status_message;
	string				content_type;
	string				content;
	vector<string>		header;
	vector<string>		cookie;
	Response();
	Response(int status, Config *conf, string content = "");
	~Response();
	Response& operator=(const Response &copy);
	bool	get_late_content();
	string	str(void);
	void			message(int fd);
};

string	get_date();

#endif