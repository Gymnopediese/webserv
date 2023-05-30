/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:32:43 by albaud            #+#    #+#             */
/*   Updated: 2023/05/30 08:25:42 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Config.hpp"

t_cgi* Config::get_cgi(Request &request)
{
	if (std::find(php.extentions.begin(), php.extentions.end(), request.file_extention) != php.extentions.end())
	{
		return &php;
	}
	for (size_t i = 0; i < cgis.size(); i++)
	{
		if (std::find(cgis[i].extentions.begin(), cgis[i].extentions.end(), request.file_extention) != cgis[i].extentions.end())
		{
			return &cgis[i];
		}
	}
	return 0;
}

int	exec(char **arguments, char **env, int in, int out)
{
	int pid = fork();
	if (pid == -1)
		throw 500;
	if (pid == 0)
	{
		int err = open("log.txt", O_WRONLY | O_CREAT , 0666);
		if (err == -1)
		{
			harl(WARNING, "Couldn't open log file, log while be written on fd STDERR_FILENO (2)");
			err = 2;
		}
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		dup2(err, STDERR_FILENO);
		if (execve(arguments[0], arguments, env) == -1)
		{
			harl(ERROR, "Execve failed");
			exit(1);
		}
	}
	return (pid);
}

void	Config::exec_cgi(Request &requests, Response &response, t_cgi &cgi)
{
	char *arguments[] = { (char*)cgi.path.c_str(), (char*)requests.file.c_str(), NULL };
	int	fd[2];
	int	post[2];

	vector<string> envstring;
	envstring.push_back("SERVER_ADDR=127.0.0.1");
	envstring.push_back("SERVER_PORT=" + to_string(port));
	envstring.push_back("SERVER_NAME=" + requests.host);
	envstring.push_back("SERVER_PROTOCOL=HTTP/1.1");
	envstring.push_back("SCRIPT_FILENAME=" + requests.file);
	envstring.push_back("PATH_INFO=" + requests.path_info);
	envstring.push_back("REDIRECT_STATUS=200");
	envstring.push_back("CONTENT_TYPE=" + requests.headers["Content-Type"]);
	envstring.push_back("CONTENT_LENGTH=" + to_string(requests.content.size()));
	envstring.push_back("QUERY_STRING=" + requests.query);
	envstring.push_back("REQUEST_METHOD=" + strtoupper(requests.type));
	envstring.push_back("ORIG_PATH_INFO=" + requests.uri);
	envstring.push_back("REQUEST_URI=" + requests.uri);
	envstring.push_back("HTTP_COOKIE=" + requests.headers["Cookie"]);
	vector<char *> env;
	for (size_t i = 0; i < envstring.size(); i++)
	{
		env.push_back((char *)envstring[i].c_str());
	}
	env.push_back(0);

	// POST SHIT
	if (pipe(post) == -1)
		throw 500;
	if (write(post[1], requests.content.c_str(), requests.content.size()) == -1)
		throw 500;
	close(post[1]);
	if (pipe(fd) == -1)
		throw 500;

	int pid = exec(arguments, &env[0], post[0], fd[1]);

	close(fd[1]);
	close(post[0]);

	response.late.pid = pid;
	response.late.fd = fd[0];
	response.late.waiting = true;
	response.late.start = get_time();
}
