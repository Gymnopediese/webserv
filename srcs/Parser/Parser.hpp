/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:42:35 by albaud            #+#    #+#             */
/*   Updated: 2023/05/27 17:58:21 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include "../header.hpp"
#include "../Config/Config.hpp"

typedef struct s_data
{
	int indentation;
	int min;
	int max;
}	t_data;

typedef struct s_line
{
	string			val;
	int				indentation;
	vector<string>	args;
}	t_line;

void			parse_cgi(vector<t_line> &lines, int &start, Config &res);
void			syntax_error(string message, int line);
void			argument_error(string arg, int level, int line);
bool			booler(string str, int line);
unsigned long long int	ft_atoi(const char *str, long long int max, int line);
string			file_exist_parser(Config &res, string loc, int line, string add = "");
string			location_exist_parser(Config &res, string loc, int line, string add = "");
t_location		parse_location(Config &conf, vector<t_line> &lines, int &start);
void			comment(string &a);

#endif