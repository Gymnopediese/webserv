/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:37:57 by albaud            #+#    #+#             */
/*   Updated: 2023/05/21 02:01:05 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

#include <iostream>
#include <chrono>
#include <ctime>    

string date()
{
	std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
	stringstream d;

    d << (now->tm_year + 1900) << '-' 
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday
         << "\n";
	return (d.str());
}

Response Config::post(Request request)
{

	for (int i = 0; i < (int)request.post.size(); i++)
	{
		if (request.post[i].filename != "")
			create_file("database/" + request.post[i].filename, request.post[i].content);
		else
			append_file("database/" + request.post[i].name, date() + request.post[i].content + "\n");
	}
	return (OK200("application/json", "okok"));
}