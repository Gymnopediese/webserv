/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:14:47 by albaud            #+#    #+#             */
/*   Updated: 2023/05/25 00:06:24 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../header.hpp"


enum requests {
	GET,
	POST,
	DELETE
};
// !!!!!!!!!!!!!!!!!!dont throw an error just ignore the dups!!!!!!!!!!!!!!!!!!!!!!!!!!
// Le premier serveur pour un host:port sera le serveur par défaut pour cet host:port !
// (ce qui signifie qu’il répondra à toutes les requêtes qui n’appartiennent pas à un !
// autre serveur).																	  !
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


class Response;

class Config
{
private:

	
public:
	// list of the host linked to that config
	vector<string>		hostnames;

	unsigned long long int		client_max_body_size;
	// the port link to that config
	int					port;
	string				root;
		// the fd of the socket of the port
	int					fd;
	map<int, string>	error_pages;
	// Dont know if necessary
	t_cgi				php;
	vector<t_cgi>		cgis;
	vector<t_location>	locations;

	Config();
	Config(vector<string> hostnames, int port, string root);
	~Config();

	t_cgi*		get_cgi(Request &request);
	t_location &get_location(Request &request);
	Response 	get(Request &request);
	Response 	delete_(Request &request);
	Response 	response(Request &request);
	void		get_html(Request &request, Response &response);
	void		exec_cgi(Request &requests, Response &response, t_cgi &cgi);
	Response	get_response(Request &request, t_location &my_location);
	void	 	_post(Request &request, Response &response);
	void		_delete(Request &request, Response &response);
};

std::ostream& operator<<(std::ostream& os, const Config& dt);

#endif