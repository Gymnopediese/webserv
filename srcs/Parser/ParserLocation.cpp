/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserLocation.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:04:08 by albaud            #+#    #+#             */
/*   Updated: 2023/05/25 11:01:41 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

void parse_return(t_location &location, vector<t_line> &lines, int &start)
{
	int	flag = 0;
	start++;
	while (start < (int)lines.size() && lines[start].indentation == 6)
	{
		if (lines[start].val != "post" && lines[start].val != "delete" && lines[start].val != "get" && lines[start].val != "all")
			syntax_error("not a valid request", start);
		location._return[lines[start].val].first = ft_atoi(lines[start].args[0].c_str(), 500, start);
		if (lines[start].args.size() < 2)
			location._return[lines[start].val].second = "";
		else
			location._return[lines[start].val].second = lines[start].args[1];
		if (lines[start].val == "all")
		{
			flag = 1;
			break ;
		}
		start++;
	}
	if (flag == 0)
		syntax_error("no return for all method", start);
	while (start < (int)lines.size() && lines[++start].indentation >= 4)
		;
}

void	parse_allowance(t_location &location, const t_line &line, int &start, int mode)
{
	for (int i = 0; i < (int)line.args.size(); i++)
	{
		if (line.args[i] != "post" && line.args[i] != "delete" && line.args[i] != "get" && line.args[i] != "all")
			syntax_error("not a valid request", start);
		if (line.args[i] == "all")
		{
			if (location.allowed["get"] == 1)
				location.allowed["get"] = mode;
			if (location.allowed["post"] == 1)
				location.allowed["post"] = mode;
			if (location.allowed["delete"] == 1)
				location.allowed["delete"] = mode;
		}
		else
			location.allowed[line.args[i]] = mode;
	}
	start++;
}

t_location parse_location(Config &conf, vector<t_line> &lines, int &start)
{
	t_location res;
	res.allowed["get"] = 1;
	res.allowed["post"] = 1;
	res.allowed["delete"] = 1;
	(void)lines;
	(void)start;
	res.path = lines[start].args[0];
	start++;
	while (start < (int)lines.size() && lines[start].indentation == 4)
	{
		if (lines[start].val == "autoindex" && ++start)
			res.repertory_listing = booler(lines[start - 1].args[0], start - 1);
		else if (lines[start].val == "index" && ++start)
			res.index = file_exist_parser(conf, lines[start - 1].args[0], start - 1);
		else if (lines[start].val == "return")
			parse_return(res, lines, start);
		else if (lines[start].val == "types")
			res.types = lines[start++].args;
		else if (lines[start].val == "download" && ++start)
			res.alias = location_exist_parser(conf, lines[start - 1].args[0], start - 1);
		else if (lines[start].val == "alias" && ++start)
			res.alias = location_exist_parser(conf, lines[start - 1].args[0], start - 1);
		else if (lines[start].val == "allow")
			parse_allowance(res, lines[start], start, 2);
		else if (lines[start].val == "deny")
			parse_allowance(res, lines[start], start, 0);
		else
			argument_error(lines[start].val, 1, start);
	}
	if (res.alias == "")
		res.path = location_exist_parser(conf, res.path, start);
	return res;
}