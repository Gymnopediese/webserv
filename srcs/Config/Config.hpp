/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:14:47 by albaud            #+#    #+#             */
/*   Updated: 2023/05/29 11:44:44 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../Response/Response.hpp"
#include "../Request/Request.hpp"

enum requests {
	GET,
	POST,
	DELETE
};

class Response;

class Config
{
private:

	
public:
	vector<string>			hostnames;
	unsigned long long int	client_max_body_size;
	int						port;
	string					root;
	int						fd;
	map<int, string>		error_pages;
	t_cgi					php;
	vector<t_cgi>			cgis;
	vector<t_location>		locations;

	Config();
	Config(vector<string> hostnames, int port, string root);
	~Config();

	t_cgi*		get_cgi(Request &request);
	t_location &get_location(Request &request);
	Response 	get(Request &request);
	Response 	response(Request &request);
	void		get_html(Request &request, Response &response);
	void		exec_cgi(Request &requests, Response &response, t_cgi &cgi);
	Response	get_response(Request &request, t_location &my_location);
	void		_post(Request &request, t_location &lo);
	void		_delete(Request &request);
};

std::ostream&			operator<<(std::ostream& os, const Config& dt);
vector<Config> 			parse_conf_file(string file);
map<string, Config*>	map_configs(vector<Config> &configs);
map<string, Config*>	map_configs(vector<Config> &configs);
string					repertory_listing(string directoryPath);
#endif