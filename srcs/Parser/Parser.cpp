/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:24:26 by albaud            #+#    #+#             */
/*   Updated: 2023/05/29 23:20:27 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

// void	parser(Config &res, vector<t_line> &lines, int &start)
// {	

// }

void parse_error(Config &conf, vector<t_line> &lines, int &start)
{
	while (++start < (int)lines.size() && lines[start].indentation == 4)
	{
		conf.error_pages[ft_atoi(lines[start].val.c_str(), 1000, start)] = file_exist_parser(conf, lines[start].args[0], start);
	}
}

// void	arg1(Config &conf, vector<string> &args, vector<string> &lines, int &start)
// {
// }

Config parse_conf(vector<t_line> &lines, int &start)
{
	Config conf;

	++start;
	while (start < (int)lines.size())
	{
		if (lines[start].indentation < 2)
			return conf;
		if (lines[start].val == "cgi")
			parse_cgi(lines, start, conf);
		else if (lines[start].val == "error")
			parse_error(conf, lines, start);
		else if (lines[start].val == "location")
			conf.locations.push_back(parse_location(conf, lines, start));
		else if (lines[start].val == "host")
			conf.hostnames = lines[start++].args;
		else if (lines[start].val == "port" && ++start)
			conf.port = ft_atoi(lines[start - 1].args[0].c_str(), 65536, start - 1);
		else if (lines[start].val == "root" && ++start)
			conf.root = location_exist_parser(conf, lines[start - 1].args[0], start - 1);
		else if (lines[start].val == "client_max_body_size" && ++start)
			conf.client_max_body_size = ft_atoi(lines[start - 1].args[0].c_str(), 0, start - 1);
		else
			argument_error(lines[start].val, 1, start);
	}
	if (conf.port == 0)
		syntax_error("no port set", start);
	if (conf.root == "")
		syntax_error("no root set", start);
	if (conf.hostnames.size() == 0)
		syntax_error("no hostname", start);
	return conf;
}

map<string, t_data>	data()
{
	map<string, t_data> res;

	res["conf"] 				= (t_data){0, 0, 0};
	res["port"] 				= (t_data){2, 1, 1};
	res["host"] 				= (t_data){2, 1, 1000};
	res["root"]					= (t_data){2, 1, 1};
	res["client_max_body_size"] = (t_data){2, 1, 1};
	res["cgi"] 					= (t_data){2, 0, 0};
	res["php"] 					= (t_data){4, 0, 0};
	res["extentions"] 			= (t_data){6, 1, 1000};
	res["path"] 				= (t_data){6, 1, 1};
	res["python"] 				= (t_data){4, 0, 0};
	res["user1"] 				= (t_data){4, 0, 0};
	res["user2"] 				= (t_data){4, 0, 0};
	res["user3"] 				= (t_data){4, 0, 0};
	res["user4"] 				= (t_data){4, 0, 0};
	res["user5"]				= (t_data){4, 0, 0};

	res["error"] 				= (t_data){2, 0, 0};

	//ADD CODE ERRORS
	res["400"] 					= (t_data){4, 1, 1};
	res["404"] 					= (t_data){4, 1, 1};
	res["405"] 					= (t_data){4, 1, 1};
	res["408"] 					= (t_data){4, 1, 1};
	res["413"] 					= (t_data){4, 1, 1};

	res["location"] 			= (t_data){2, 1, 1};
	res["tryfile"] 				= (t_data){4, 1, 1};
	res["return"] 				= (t_data){4, 0, 0};
	res["get"] 					= (t_data){6, 1, 2};
	res["post"] 				= (t_data){6, 1, 2};
	res["delete"] 				= (t_data){6, 1, 2};
	res["all"] 					= (t_data){6, 1, 2};
	res["alias"] 				= (t_data){4, 1, 1};
	res["listing"] 				= (t_data){4, 1, 1};
	res["index"] 				= (t_data){4, 1, 1};
	res["download"] 				= (t_data){4, 1, 4};
	res["allow"] 				= (t_data){4, 1, 4};
	res["deny"] 				= (t_data){4, 1, 1};
	res["types"] 				= (t_data){4, 1, 1000};

	return (res);
}

vector<Config> parse_conf_file(string file)
{
	(void)file;
	vector<Config> res;
	vector<t_line> lines;

	map<string, t_data>	d = data();

	vector<string> temp = split(file_to_str(file), "\n");
	for (int i = 0; i < (int)temp.size(); i++)
	{
		comment(temp[i]);
		if (trim(temp[i]) == "")
			temp.erase(temp.begin() + i--);
	}
	for (int i = 0; i < (int)temp.size(); i++)
	{
		t_line			add;
		vector<string>	stemp = split(temp[i], ":");
	
		if (stemp.size() < 2)
			syntax_error("missing :", i);
		if (stemp.size() > 2)
		{
			vector<string> neww;
			neww.push_back(stemp[0]);
			neww.push_back(join(stemp, 1, ':'));
			stemp = neww;
		}
		add.indentation = spaces(stemp[0]);
		trim(stemp);
		add.val = stemp[0];
		if (stemp[1] != "")
			add.args = split(stemp[1], " ");
		if (d.find(add.val) == d.end())
			syntax_error("invalid keyword", i);
		if (d[add.val].indentation != add.indentation)
			syntax_error("bad indentation", i);
		if ((int)add.args.size() < d[add.val].min || (int)add.args.size() > d[add.val].max)
			syntax_error("invalid argument number", i);
		lines.push_back(add);
	}
	for (int i = 0; i < (int)lines.size();)
	{
		if (lines[i].val != "conf" && i++)
			continue ;
		res.push_back(parse_conf(lines, i));
	}
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
			res[*k + ":" + to_string(configs[i].port)] = &configs[i];
		}
	}
	return (res);
}