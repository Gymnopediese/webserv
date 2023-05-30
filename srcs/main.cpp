/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:44:50 by albaud            #+#    #+#             */
/*   Updated: 2023/05/29 23:23:03 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Server.hpp"



int harl_mode;

int main(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
		error("invalid args: ./webserv <config.yaml>");
	harl_mode = 0;
	if (argc > 3)
		harl_mode = 0;
	Server server(argv[1]);

	server.loop();
}