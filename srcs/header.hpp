/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 00:46:01 by albaud            #+#    #+#             */
/*   Updated: 2023/05/21 01:56:21 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
# define HEADER_HPP

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sys/socket.h>
#include <poll.h>
#include <fstream>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sstream>

using std::string;
using std::cout;
using std::vector;
using std::map;
using std::endl;


#include "Utils/errors.hpp"
#include "Request/Request.hpp"
#include "Response/Response.hpp"
#include "Config/Config.hpp"

typedef struct s_socket
{
	int					fd;
	socklen_t			length;
	struct sockaddr_in	adress;
}	t_socket;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

using namespace std;

class Config;

vector<Config> 			parse_conf_file(string file);
map<string, Config*>	map_configs(vector<Config> &configs);

// open a socket 
t_socket			open_socket(int port);
// open all socket 
map<int, t_socket>	open_sockets(vector<Config> &configs, vector<pollfd>&fds);


void			error(const char *msg);
string			join(vector<string> to_split, int start = 0, char del = ' ');

vector<string>	split(string to_split, char del = ' ');
vector<string>	split(string to_split, string del);

string			exec_php(string php);

// map the configs 😱
map<string, Config*> map_configs(vector<Config> &configs);

string file_to_str(string filename);
bool file_exist(const std::string& name);


void 	append_file(const std::string& filename, const std::string& content);
void	create_file(string filename, string content);

// template <typename T>
// void	print(vector<T> v)
// {
// 	for (typename vector<T>::iterator i = v.begin(); i < v.end(); i++)
// 		cout << *i << endl;
// }

// template <typename T, typename A>
// void	print(map<T, A> v)
// {
// 	for (typename map<T, A>::iterator i = v.begin(); i < v.end(); i++)
// 		cout << *i << endl;
// }
#endif