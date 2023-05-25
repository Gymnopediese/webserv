/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:48:22 by albaud            #+#    #+#             */
/*   Updated: 2023/05/25 00:52:45 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.hpp"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void strtolower(string &a) {
	int i = -1;
    while(a[++i])
		a[i] = tolower(a[i]);
}

void strtoupper(string &a) {
	int i = -1;
    while(a[++i])
		a[i] = toupper(a[i]);
}

std::string trim(const std::string& str) {
    int s;
	int	e;

	s = -1;
	e = str.length();
	while (str[++s] && std::isspace(str[s]));
	while (--e >= 0 && std::isspace(str[e]))
		;
    return str.substr(s, e - s + 1);
}

void	trim(vector<string>& str)
{
	for (int i = 0; i < (int)str.size(); i++)
	{
		str[i] = trim(str[i]);
	}
}

int	spaces(string s)
{
	int i = -1;
	while(s[++i] == ' ');
	return (i);
}

void printr(string r)
{
    size_t found = r.find('\r');
    while (found != std::string::npos) {
        r[found] = '$';
       found = r.find('\r', found + 1);
    }
	cout << r << endl;
}

unsigned long long get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return static_cast<unsigned long long>(tv.tv_sec) * 1000000 +
           static_cast<unsigned long long>(tv.tv_usec);
}

pair<string, string>	split2(string to_split, string del)
{
	pair<string, string>	res;
	int						ind;
	
	res.second = "";
	if ((ind = to_split.find(del)) > -1)
	{
		res.first = to_split.substr(0, ind);
		res.second = to_split.substr(ind + del.length());
	}
	else
		res.first = to_split;
	return (res);
}

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

string	join(vector<string> to_split, int start, int end, string del)
{
	string	res = "";
	
	for (int i = start; i < end; i++)
	{
		res += to_split[i];
		if (i < (int) to_split.size() - 1)
			res += del;
	}
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