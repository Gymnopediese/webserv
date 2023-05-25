/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserValidator.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:04:55 by albaud            #+#    #+#             */
/*   Updated: 2023/05/22 22:51:43 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

bool booler(string str, int line)
{
	if (str == "on" || str == "true")
		return (true);
	if (str == "off" || str == "false")
		return (true);
	syntax_error("invalid bolean", line);
	return (false);
}


unsigned long long int	ft_atoi(const char *str, long long int max, int line)
{
	int result = 0;
    int sign = 1;
    int i = 0;

    // Skip leading whitespace
    while (str[i] == ' ' || str[i] == '\t') {
        i++;
    }

    // Check for optional sign
    if (str[i] == '-' || str[i] == '+') {
        sign = (str[i++] == '-') ? -1 : 1;
    }

    // Process digits
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i++] - '0');
    }
	if (sign == -1)
		syntax_error("atoi: cannot be negatif", line);
	if (result > max && max > 0)
		syntax_error("atoi: number too big", line);
	if (str[i] == 0)
		return result * sign;
	if (str[i + 1] == 0 && str[i] == 'k')
		return result * sign * 1000;
	if (str[i + 1] == 0 && str[i] == 'm')
		return result * sign * 1000000;
	if (str[i + 1] == 0 && str[i] == 'g')
		return result * sign * 1000000000;
	cout << str << endl;
	syntax_error("atoi: text in int", line);
	return (0);
}

string	file_exist_parser(Config &res, string loc, int line, string add)
{
	cout << res.root + add + loc << endl;
	if (!file_exist(res.root + add + loc) && !file_exist(loc))
		syntax_error("non existing file", line);
	return (loc);
}

string	location_exist_parser(Config &res, string loc, int line, string add)
{
	cout << res.root + add + loc << endl;
	if (dir_exist(res.root + add + loc) == false)
		syntax_error("not a directory", line);
	return (loc);
}