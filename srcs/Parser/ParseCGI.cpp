/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseCGI.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:41:54 by albaud            #+#    #+#             */
/*   Updated: 2023/05/22 20:17:40 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

void	parse_cgi(vector<t_line> &lines, int &start, Config &res)
{
	map<string, string> used;
	start++;
	while (start < (int)lines.size() && lines[start].indentation == 4)
	{
		t_cgi			cgi;

		cgi.name = lines[start].val;
		bool a = false;
		bool b = false;
		redo:
		start++;
		if (lines[start].val == "extentions")
		{
			cgi.extentions = lines[start].args;
			a = true;
			goto redo;
		}
		if (lines[start].val == "path")
		{
			cgi.path = file_exist_parser(res, lines[start].args[0], start);
			b = true;
			goto redo;
		}
		if (cgi.name == "php")
			res.php = cgi;
		else
			res.cgis.push_back(cgi);
		if (a == false)
			syntax_error("missing extentions", start);
		if (b == false)
			syntax_error("missing path", start);
	}
}