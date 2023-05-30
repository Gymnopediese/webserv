/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:38:59 by albaud            #+#    #+#             */
/*   Updated: 2023/05/30 08:06:02 by albaud           ###   ########.fr       */
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



void	Server::accept_clients()
{
	for (size_t i = 0; i < socket_in.size(); i++)
	{
		if (!(pollfds[socket_in[i]].revents & POLLIN))
			continue ;
		t_client		new_client;
		new_client.socket.fd = accept(socket_in[i], (struct sockaddr *) &new_client.socket.adress, &new_client.socket.length);
		if (new_client.socket.fd < 0) 
			error("accept error");
		stringstream a;
		a << "from " << inet_ntoa(new_client.socket.adress.sin_addr)
			<< " port " << ntohs(new_client.socket.adress.sin_port)  << " fd " <<  new_client.socket.fd;
		harl(INFOS, a.str(), MAGENTA);
		pollfds[new_client.socket.fd] = (pollfd){new_client.socket.fd, POLLIN, 0};
		clients[new_client.socket.fd] = new_client;
		client_in.push_back(new_client.socket.fd);
		fcntl(new_client.socket.fd, F_SETFL, O_NONBLOCK);
	}
}

void	Server::get_clients_late_requests()
{
	for (size_t i = 0; i < late_in.size(); i++)
	{
		int			fd = late_in[i];
		Response	&response = clients[clients[fd].socket.fd].response;

		if (!(get_time() - response.late.start > 10000000 || pollfds[fd].revents & POLLIN))
			continue ;
		try
		{
			if (!response.get_late_content())
				continue ;
			pollfds[response.late.client] = (pollfd){response.late.client, POLLOUT, 0};
			client_out.push_back(response.late.client);
		}
		catch (int err)
		{
			cout << err << endl;
			pollfds[response.late.client] = (pollfd){response.late.client, POLLOUT, 0};
			client_out.push_back(response.late.client);
			response = Response(err, clients[clients[fd].socket.fd].config);
			response.content = response.str();
		}
		close(fd);
		pollfds.erase(fd);
		late_in.erase(late_in.begin() + i--);
	}
}

void	Server::request_to_response(int fd)
{
	Request		&request = clients[fd].request;
	Response	&response = clients[fd].response;
	pollfd		p;


	if (request.type == "post")
		request.get_post();
	try
	{
		if (request.client_max_body_size - request.content.length() < 0)
			throw 413;
		if (response.status == 0)
			response = clients[fd].config->response(request);
	}
	catch (int err)
	{
		response = Response(err, clients[fd].config);
	}
	if (response.status >= 400 || response.late.waiting)
		request.file_extention = ".html";
	response.content_type = get_content_type(request.file_extention);
	response.late.client = fd;
	if (response.late.waiting)
	{
		p = (pollfd){clients[fd].response.late.fd, POLLIN, 0};
		late_in.push_back(p.fd);
		clients[p.fd].socket.fd = fd;
	}
	else
	{
		response.content = response.str();
		p = (pollfd){fd, POLLOUT, 0};
		client_out.push_back(p.fd);
	}
	pollfds.erase(fd);
	pollfds[p.fd] = p;
}

#include <sys/stat.h>

void	Server::get_clients_requests()
{
	for (size_t i = 0; i < client_in.size(); i++)
	{
		int fd = client_in[i];
		Request &request = clients[fd].request;
		Response &response = clients[fd].response;
		
		try
		{
			if (get_time() - request.start_time > 10000000)
				throw 408;
			if (!(pollfds[fd].revents & POLLIN))
				continue;
			if (request.recv(fd))
			{
				request.message(fd);
				if (configs_map.find(request.host + ":" + request.port) == configs_map.end())
					throw 421;
				clients[fd].config = configs_map[request.host + ":" + request.port];
				request.client_max_body_size = clients[fd].config->client_max_body_size;
				if (request.client_max_body_size < (long long)request.content_length)
					throw 413;
			}
			if (!(request.content_length == request.content.length() || (request.chunked && request.content.substr(request.content.size() - 5) == "\r\n0\r\n")))
				continue ;
			request_to_response(fd);
			client_in.erase(client_in.begin() + i);
			i--;
		}
		catch (int err)
		{
			//TODO CLOSE CLIENT
			cout << "not even an erro beach" << endl;
			if (err == 0)
				harl(WARNING, "Client connexion was close by a third part user");
			if (err == -1)
				harl(ERROR, "error reading client socket");
			if (err <= 0)
			{
				i--;
				disconnect_client(fd);
				continue ;	
			}
			response = Response(err, 0);
			response.content = response.str();
			pollfds[fd] = (pollfd){fd, POLLOUT, 0};
			client_out.push_back(fd);
			client_in.erase(client_in.begin() + i);
			i--;
		}

	}
}

void	Server::send_clients_response()
{
	for (size_t i = 0; i < client_out.size(); i++)
	{
		int fd = client_out[i];
		if (!(pollfds[fd].revents & POLLOUT))
			continue;
		ssize_t d = send(fd, clients[fd].response.content.c_str(),
			std::min(clients[fd].response.content.size(), (size_t)10000), 0);
		if ((int)d > 0)
		{
			clients[fd].response.content = clients[fd].response.content.substr(d);
			continue ;
		}
		if (d == -1)
			harl(ERROR, "error while writing in client socket");
		else
			clients[fd].response.message(fd);
		pollfds.erase(fd);
		clients.erase(fd);
		close(fd);
		client_out.erase(client_out.begin() + i--);
	}
}

void	Server::disconnect_client(int fd)
{
	cout << fd << endl;
	for (vector<int>::iterator i = client_in.begin(); i != client_in.end(); i++)
	{
		if (*i == fd)
		{
			client_in.erase(i);
			break;
		}
	}
	for (vector<int>::iterator i = client_out.begin(); i != client_out.end(); i++)
	{
		if (*i == fd)
		{
			client_out.erase(i);
			break;
		}
	}
	for (vector<int>::iterator i = late_in.begin(); i != late_in.end(); i++)
	{
		if (*i == fd)
		{
			close(clients[fd].response.late.fd);
			kill(clients[fd].response.late.pid, SIGKILL);
			late_in.erase(i);
			break;
		}
	}
	for (vector<int>::iterator i = socket_in.begin(); i != socket_in.end(); i++)
	{
		if (*i == fd)
		{
			socket_in.erase(i);
			break;
		}
	}
	close(fd);
	pollfds.erase(fd);
	clients.erase(fd);
}

void	Server::wait_poll()
{
	//A OPTIIIIIIIIII
	pollfd fds[pollfds.size()];
	int	c = 0;
	for (map<int, pollfd>::iterator i = pollfds.begin(); i != pollfds.end(); i++)
		fds[c++] = i->second;
	// cout << "a" << endl;
	int ret = poll(fds, pollfds.size(), 10000);
	if (ret == 0)
		harl(DEBUG, "Poll timedout to check for looping requests/responses");
	// cout << "b" << endl;
	size_t max = pollfds.size();
	for (size_t i = 0; i < max; i++)
	{
		pollfds[fds[i].fd].revents = fds[i].revents;
	}
	if (ret == -1)
		harl(FATAL, "poll internal error");
}

void	Server::loop()
{
	while (true)
	{
		wait_poll();
		send_clients_response();
		get_clients_late_requests();
		get_clients_requests();
		accept_clients();
	}
}