/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subfrom.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 08:34:54 by albaud            #+#    #+#             */
/*   Updated: 2023/05/22 08:35:43 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.hpp"

string	subfrom(string str, string sub)
{
	int		start;

	start = str.find(sub);
	if (start == -1)
		return ("");
	return (str.substr(start + sub.length()));
}

string	subfromto(string str, string sub, string subend)
{
	int		start;
	int		end;

	start = str.find(sub);
	end = str.find(subend, start + sub.length());
	if (start == -1 || end == -1)
		return ("");
	start += sub.length();
	return (str.substr(start, end - start));
}