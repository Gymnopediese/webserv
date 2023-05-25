/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:37:57 by albaud            #+#    #+#             */
/*   Updated: 2023/05/25 11:01:06 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

void Config::_delete(Request &request, Response &response)
{
	vector<string>	t = split(request.file, "/");
	string		to_delete = "trash/" + t[t.size() - 1];

	cout << " ok ok " << endl;
	if (std::rename(request.file.c_str(), to_delete.c_str()) != 0)
	{
       response = Response(401, *this);
    }
	else
	{
        printf("File moved successfully\n");
    }
}