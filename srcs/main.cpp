/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:44:50 by albaud            #+#    #+#             */
/*   Updated: 2023/05/24 21:11:50 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"


vector<char *>	envp;

int main(int argc, char **argv, char **env)
{
	if (argc != 2)
		error("invalid args boy");
    for (int i = 0; env[i]; ++i)
        envp.push_back(env[i]);
	Server server(argv[1]);

	server.loop();
}