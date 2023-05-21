/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sockets.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:26:45 by albaud            #+#    #+#             */
/*   Updated: 2023/05/20 00:57:35 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.hpp"

t_socket	open_socket(int port)
{
	t_socket res;
	res.fd =  socket(AF_INET, SOCK_STREAM, 0);
	if (res.fd < 0) 
		error("ERROR opening socket");
	bzero((char *) &res.adress, sizeof(res.adress));

	/* setup the host_addr structure for use in bind call */
	// server byte order
	res.adress.sin_family = AF_INET;  

	// automatically be filled with current host's IP address
	res.adress.sin_addr.s_addr = INADDR_ANY;  

	// convert short integer value for port must be converted into network byte order
	res.adress.sin_port = htons(port);

	// bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
	// bind() passes file descriptor, the address structure, 
	// and the length of the address structure
	// This bind() call will bind  the socket to the current IP address on port, portno
	if (setsockopt(res.fd, SOL_SOCKET, SO_REUSEADDR, &res.adress, sizeof(res.adress)) == -1)
	{
		 error("ERROR on setsockopt");
	}
	if (bind(res.fd, (struct sockaddr *) &res.adress, sizeof(res.adress)) == -1) 
        error("ERROR on binding");
	return res;
}

//	open_
map<int, t_socket>	open_sockets(vector<Config> &configs, vector<pollfd> &fds)
{
	map<int, t_socket>	res;
	vector<int>			done;

	for (vector<Config>::iterator config = configs.begin(); config < configs.end(); config++)
	{
		if (std::find(done.begin(), done.end(), (*config).port) == done.end())
		{
			res[(*config).port] = (open_socket((*config).port));
			done.push_back((*config).port);
			fds.push_back((pollfd){res[(*config).port].fd, POLLIN, POLLIN});
			listen(res[(*config).port].fd, 1024);
		}
	}
	return (res);
}

