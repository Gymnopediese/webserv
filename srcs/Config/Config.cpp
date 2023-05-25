/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:34:30 by albaud            #+#    #+#             */
/*   Updated: 2023/05/24 14:21:26 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config(vector<string> hostnames, int port, string root) : hostnames(hostnames), port(port), root(root){}
Config::Config() : port(){}
Config::~Config(){}

std::ostream& operator<<(std::ostream& os, const t_cgi& dt)
{
    os << "name: " << dt.name << endl;
    os << "path: " << dt.path << endl;
    os << "extentions: " << dt.extentions << endl;
    return os;
}


std::ostream& operator<<(std::ostream& os, const t_location& dt)
{
    os << "###############" << dt.path << "##################"<<endl;
    os << "alias: " << dt.alias << endl;
	os << "allowed: "<< (dt.allowed) << endl;
	os << "database: " << dt.database << endl;
	os << "index: " << dt.index << endl;
	os << "map: " << dt._return << endl;
	os << "types: " << dt.types << endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Config& dt)
{
    os << "root: " << dt.php << endl;
	os << "port: " << dt.port << endl;
	os << "client_max_body_size: " << dt.client_max_body_size << endl;
	os << "hostnames: " << (dt.hostnames) << endl;
	os << "error_pages:\n" << dt.error_pages << endl;
	os << "###########PHP########: " << endl;
	cout << dt.php << endl;
	os << "###########CGIS########: " << endl;
	cout << dt.cgis << endl;
	os << "###########LOCATIONS########: " << endl;
	cout << dt.locations << endl;
    return os;
}
