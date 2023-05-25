/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:38:59 by albaud            #+#    #+#             */
/*   Updated: 2023/05/25 11:08:10 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(){};
Server::Server(string config_file)
{
	configs = parse_conf_file(config_file);
	configs_map = map_configs(configs);
	open_sockets();
}
Server::~Server(){}

void	Server::repond(Response &response, int fd)
{
	string	r = response.str();
	cout << "response : " << r.substr(0, 400) << endl;
	send(fd, r.c_str(), r.length(), 0);
	close(fd);
}

void	Server::accept_clients()
{
	for (size_t i = 0; i < sockets.size(); i++)
	{
		if (!(fds[i].revents & POLLIN))
			continue ;
		t_socket	newClient;
		newClient.fd = accept(fds[i].fd, (struct sockaddr *) &newClient.adress, &newClient.length);
		if (newClient.fd < 0) 
			error("accept error");
		printf("server: got connection from %s port %d fd %i\n",
			inet_ntoa(newClient.adress.sin_addr), ntohs(newClient.adress.sin_port), newClient.fd);
		fds.push_back((pollfd){newClient.fd, POLLIN, POLLIN});
		fcntl(newClient.fd, F_SETFL, O_NONBLOCK);
	}
}

void	Server::response_late_client()
{
	size_t	start = sockets.size();
	size_t	end = start + responses.size();

	for (size_t i = start; i < end; i++)
	{
		if (!responses[i - start].get_late_content())
			continue ;
		repond(responses[i - start], responses[i - start].late.client);
		cout << responses[i - start].late.client << endl;
		responses.erase(responses.begin() + i - start);
		fds.erase(fds.begin() + i);
		i--;
		end--;
	}
}

void	Server::get_clients_requests()
{
	size_t start = sockets.size() + responses.size();
	for (size_t i = start; i < fds.size(); i++)
	{
		if (!(fds[i].revents & POLLIN))
			continue;
		cout << "##################CLIENT REQUEST##################" << endl;
		Request		request(fds[i].fd);
		
		if (configs_map.find(request.host + ":" + request.port) == configs_map.end())
			error("mashala y a pas ce host bro sprh");
		Config		*conf = configs_map[request.host + ":" + request.port];
		request.get_body(conf->client_max_body_size);

		
		cout << "##################server response##################" << endl;
		Response	response;
		response = conf->response(request);
		response.late.client = fds[i].fd;

		if (response.get_late_content())
		{
			repond(response, fds[i].fd);
		}
		else
		{
			responses.insert(responses.begin(), response);
			fds.insert(fds.begin() + sockets.size(), ((pollfd){response.late.fd, POLLIN, POLLIN}));
			i++;
		}
		fds.erase(fds.begin() + i);
		i--;
	}
}

void	Server::loop()
{
	while (true)
	{
		int ret = poll(&fds[0], fds.size(), 10000);
		if (ret == -1)
		{
			error("Erreur de la fonction poll.");
		}
		get_clients_requests();
		response_late_client();
		accept_clients();
	}
}