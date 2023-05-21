/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:44:50 by albaud            #+#    #+#             */
/*   Updated: 2023/05/21 02:50:02 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

string	recv_message(int fd)
{
	string		res = "";
	char		b[1024];
	int			size;
	
	size = 1;
	while (size)
	{
		size = recv(fd, b, 1023, 0);
		if (size <= 0)
		{
			perror("retars");
			break;
		}
		b[size] = 0;
        res.append(b, size);
		//cout.write(b, size);

	}
	return (res);
}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void accept_clients(map<int, t_socket> &sockets, vector<pollfd> &fds)
{
	for (int i = 0; i < (int)sockets.size(); i++)
	{
		if (fds[i].revents & POLLIN)
		{
			t_socket	newClient;
			newClient.fd = accept(fds[i].fd, (struct sockaddr *) &newClient.adress, &newClient.length);
			if (newClient.fd < 0) 
				error("accept error");
			printf("server: got connection from %s port %d fd %i\n",
				inet_ntoa(newClient.adress.sin_addr), ntohs(newClient.adress.sin_port), newClient.fd);
			fds.push_back((pollfd){newClient.fd, POLLIN, POLLIN});
			//fds[i].clients.push_back(newClient);
			fcntl(newClient.fd, F_SETFL, O_NONBLOCK);
		}

		if (fds[i].revents & POLLOUT) {
			cout << "pollout" << endl; 
		}
	}
}

void	get_clients_requests(int start, vector<pollfd> &fds, map<string, Config *> &configs_map)
{
	for (int i = start; i < (int)fds.size(); i++)
	{
		if (fds[i].revents & POLLIN)
		{
			cout << "##################CLIENT REQUEST##################" << endl;
			string b = recv_message(fds[i].fd);
			if (b == "")
				continue ;

			Request		request(b);
			//cout << request.host << " " << request.port << endl;
	
			Config		*conf = configs_map[request.host + ":" + request.port];

			Response	response;
			if (request.type == "GET")
				response = conf->get(request);
			else if (request.type == "POST")
				response = conf->post(request);
			else if (request.type == "DELETE")
				response = conf->delete_(request);
	
			string	r = response.str();
			cout << "##################server response##################" << endl;
			cout << r.substr(0, 400) << endl;
			send(fds[i].fd, r.c_str(), r.length(), 0);
			fds.erase(fds.begin() + i);
			close(fds[i].fd);
			i--;
			continue;
		}
		if (fds[i].revents & POLLOUT) {
			cout << "salut yess" << endl;
		}
	}
}

int main(int argc, char **argv, char **envp)
{
	(void) envp;
	(void) argc;
	map<int, t_socket>		sockets;
	vector<pollfd>			fds;
	vector<Config>			configs = parse_conf_file(argv[0]);
	map<string, Config *>	configs_map = map_configs(configs);
	sockets = open_sockets(configs, fds);
	while (true)
	{
		int ret = poll(&fds[0], fds.size(), -1);
		if (ret == -1) {
       		std::cerr << "Erreur de la fonction poll." << std::endl;
        	exit(1);
		}
		get_clients_requests(sockets.size(), fds, configs_map);
		accept_clients(sockets, fds);
	}
	return 0;
}