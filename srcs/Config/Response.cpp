/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:23:42 by albaud            #+#    #+#             */
/*   Updated: 2023/05/25 13:58:10 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

t_location &Config::get_location(Request &request)
{
	t_location &res = locations[0];

	size_t	max = 0;
	for (size_t i = 0; i < locations.size(); i++)
	{
		size_t l = locations[i].path.length();
		if (request.file.compare(0, l, locations[i].path) == 0 && max < l)
		{
			res = locations[i];
			max = l;
		}
	}
	return (res);
}

void Config::get_html(Request &request, Response &response)
{
	t_cgi	*cgi = get_cgi(request);

	cout << cgi << endl;
	if (!cgi || request.type == "delete")
	{
		response.content = file_to_str(request.file);
		return ;
	}
	exec_cgi(request, response, *cgi);
}

Response	Config::get_response(Request &request, t_location &my_location)
{
	cout << request.type << "$ " << my_location.path << endl;
	if (my_location._return.find("all") == my_location._return.end())
		return Response(200, *this);
	else if (my_location._return.find(request.type) != my_location._return.end())
		return Response(my_location._return[request.type].first, *this, my_location._return[request.type].second);
	else
		return Response(my_location._return["all"].first, *this, my_location._return["all"].second);
}

Response Config::response(Request &request)
{
	t_location &my_location = get_location(request);

	if (my_location.alias != "")
		request.file = root + my_location.alias + request.file.substr(my_location.path.size());
	else
		request.file = root + request.file;
	if (dir_exist(request.file))
		request.file += my_location.index;
	else if (!file_exist(request.file))
		return (Response(404, *this)); // NOT fOunf
	if (my_location.allowed.find(request.type) == my_location.allowed.end())
		return (Response(400, *this)); // BADREQUEST
	if (my_location.allowed[request.type] == 0)
		return (Response(405, *this)); // NOT ALLOWED
	Response response = get_response(request, my_location);
	if (request.type == "post")
		_post(request, response);
	if (response.status >= 300)
		return (response);
	get_html(request, response);
	if (request.type == "delete")
		_delete(request, response);
	// if (request.type == "get")
	// 	response = get(request);
	// else if (request.type == "post")
	// 	response = post(request);
	// else if (request.type == "delete")
	// 	response = delete_(request);
	// else
	// 	response = Response(400, *this);
	return (response);
}