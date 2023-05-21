/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:24:26 by albaud            #+#    #+#             */
/*   Updated: 2023/05/20 10:10:57 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.hpp"

vector<Config> parse_conf_file(string file)
{
	(void)file;
	vector<Config> res;
	vector<string> host1;
	vector<string> host2;
	vector<string> host3;
	
	host1.push_back("localhost");
	host2.push_back("localhost");
	host3.push_back("albaud.42.ch");
	host3.push_back("www.albaud.42.ch");
	res.push_back(Config(host1, 4343, "./conf"));
	res.push_back(Config(host2, 4444, "./help"));
	res.push_back(Config(host3, 4343, "./conf2"));
	return (res);
}

map<string, Config*> map_configs(vector<Config> &configs)
{
	map<string, Config*> res;

	(void) configs;
	for (int i = (int)configs.size() - 1; i >= 0; i--)
	{
		for (vector<string>::iterator k = configs[i].hostnames.begin(); k < configs[i].hostnames.end(); k++)
		{
			cout << *k + ":" + to_string(configs[i].port) << endl;
			res[*k + ":" + to_string(configs[i].port)] = &configs[i];
		}
	}
	return (res);
}