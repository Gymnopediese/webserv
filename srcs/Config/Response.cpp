/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:23:42 by albaud            #+#    #+#             */
/*   Updated: 2023/05/30 08:22:50 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

t_location &Config::get_location(Request &request)
{
	t_location *res = 0;

	size_t	max = 0;
	for (size_t i = 0; i < locations.size(); i++)
	{
		size_t l = locations[i].path.length();
		if (request.file.compare(0, l, locations[i].path) == 0 && max < l)
		{
			res = &locations[i];
			max = l;
		}
	}
	return (*res);
}

void Config::get_html(Request &request, Response &response)
{
	t_cgi	*cgi = get_cgi(request);

	if (!cgi || request.type == "delete")
	{
		response.content = file_to_str(request.file);
		return ;
	}
	exec_cgi(request, response, *cgi);
}

Response	Config::get_response(Request &request, t_location &my_location)
{
	if (my_location._return.find("all") == my_location._return.end())
		return Response(200, this);
	else if (my_location._return.find(request.type) != my_location._return.end())
		return Response(my_location._return[request.type].first, this, my_location._return[request.type].second);
	else
		return Response(my_location._return["all"].first, this, my_location._return["all"].second);
}

Response Config::response(Request &request)
{
	t_location &my_location = get_location(request);

	Response response = get_response(request, my_location);

	if (my_location.allowed[request.type] == 0)
		throw 405;
	if (my_location.alias != "")
		request.file = root + my_location.alias + request.file.substr(my_location.path.size());
	else
		request.file = root + request.file;
	if (access(request.file.c_str(), R_OK) != 0)
		throw 403;
	if (dir_exist(request.file) && my_location.index != "" && file_exist(root + my_location.path + my_location.index))
	{
		request.file = root + my_location.path + my_location.index;
		request.file_extention = ".html";
	}
	else if (dir_exist(request.file) && my_location.repertory_listing)
	{
		request.file_extention = ".html";
		response.content = repertory_listing(request.file);
	}
	else if (dir_exist(request.file))
		throw 403;
	else if (!file_exist(request.file))
		throw 404;
	if (response.status >= 300)
		return (response);
	if (request.type == "delete")
		_delete(request);
	else if (response.content == "")
		get_html(request, response);
	if (!response.late.waiting && request.type == "post")
		_post(request, my_location);
	return (response);
}