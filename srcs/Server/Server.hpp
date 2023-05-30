/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:14:50 by albaud            #+#    #+#             */
/*   Updated: 2023/05/30 07:58:31 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "../header.hpp"
#include "../Config/Config.hpp"
#include "../Utils/errors.hpp"

typedef struct s_client
{
	t_socket					socket;
	int							fd;
	Request						request;
	Response					response;
	Config						*config;
}	t_client;


class Server
{
private:

	vector<int>				socket_in;
	vector<int>				client_in;
	vector<int>				client_out;
	vector<int>				late_in;

	map<int, pollfd>		pollfds;
	map<int, t_client>		clients;
	map<int, t_socket>		sockets;
	vector<Config>			configs;
	map<string, Config *>	configs_map;

	Server(/* args */);
	void					open_sockets(void);
	bool					repond(Response &response, int fd);
	void					accept_clients();
	void					disconnect_client(int fd);
	void					get_clients_late_requests();
	void					get_clients_requests();
	void					send_clients_response();
	void					get_clients_body();
	void					request_to_response(int i);
	void					wait_poll();
public:
	Server(string config_file);
	~Server();
	void	loop();
};

t_socket			open_socket(int port);
map<int, t_socket>	open_sockets(vector<Config> &configs, vector<pollfd>&fds);
#endif