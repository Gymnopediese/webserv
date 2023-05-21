/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:37:57 by albaud            #+#    #+#             */
/*   Updated: 2023/05/21 02:53:29 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Response Config::get(Request request)
{
	string html;

	cout << root + request.file << endl;
    if (!file_exist(root + request.file))
		return (OK200("html", "404"));
	if (request.file_extention == "php")
		html = exec_php(root + request.file);
	else
		html = file_to_str(root + request.file);
	if (request.file == "/favicon.ico")
		return (FAVICON(html));
	return (OK200("html", html));
}