/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:48:22 by albaud            #+#    #+#             */
/*   Updated: 2023/05/20 11:08:52 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.hpp"

vector<string>	split(string to_split, string del)
{
	vector<string>	res;
	int				ind;
	
	while ((ind = to_split.find(del)) > -1)
	{
		to_split[ind] = 0;
		res.push_back(to_split.substr(0, ind));
		to_split = to_split.substr(ind + del.length());
	}
	res.push_back(to_split);
	return (res);
}

string	resplace(string a, string old, string _new)
{
	size_t pos = a.find(old);
    while (pos != std::string::npos) {
    	a = a.replace(pos, old.length(), _new);
        pos = a.find(old, pos + _new.length());
    }
	return a;
}

vector<string>	split(string to_split, char del)
{
	vector<string>	res;
	int				ind;

	to_split = resplace(to_split, "\r", "");
	while ((ind = to_split.find(del)) > -1)
	{
		to_split[ind] = 0;
		res.push_back(to_split.substr(0, ind));
		to_split = to_split.substr(ind + 1);
	}
	res.push_back(to_split);
	return (res);
}

string	join(vector<string> to_split, int start, char del)
{
	string	res = "";
	
	for (int i = start; i < (int) to_split.size(); i++)
	{
		res += to_split[i];
		if (i < (int) to_split.size() - 1)
			res += del;
	}
	return (res);
}