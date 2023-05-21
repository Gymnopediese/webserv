/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:14:47 by albaud            #+#    #+#             */
/*   Updated: 2023/05/21 01:20:22 by albaud           ###   ########.fr       */
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

	// the fd of the socket of the port
	int					fd;

	// default html if the request point to a directory
	string				index;

	// the allowed request on this config, uses requests enum
	// can be changed to map or whetever feels the best
	int 				allowed[3];

	map<int, string>	error_pages;
	// list of the aliases linked to that config
	map<string, string>	aliases;

	// list of the redirections linked to that config
	map<string, string>	redirections;


	// dont know lol
	bool				repertory_listing;

	// Dont know if necessary
	vector<string>	php_cgi_extentions;
	vector<string>	python_cgi_extentions;
	
public:
	// list of the host linked to that config
	vector<string>	hostnames;
	// the port link to that config
	const int				port;
	const string			root;

	Config();
	Config(vector<string> hostnames, int port, string root);
	~Config();

	Response get(Request request);
	Response post(Request request);
	Response delete_(Request request);
};
#endif