/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:14:50 by albaud            #+#    #+#             */
/*   Updated: 2023/05/24 20:50:02 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "../header.hpp"

// definir comme ca les reponse error et normal

class Server
{
private:
	map<int, t_socket>		sockets;
	vector<pollfd>			fds;
	vector<Config>			configs;
	map<string, Config *>	configs_map;
	vector<Response>		responses;

	Server(/* args */);
	void					open_sockets(void);
	void					repond(Response &response, int fd);
	void					accept_clients();
	void					response_late_client();
	void					get_clients_requests();
public:
	Server(string config_file);
	~Server();
	void	loop();
};

#endif