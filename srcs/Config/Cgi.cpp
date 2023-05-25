/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:32:43 by albaud            #+#    #+#             */
/*   Updated: 2023/05/25 11:00:57 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../header.hpp"

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
	if (pid == 0)
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		
		if (execve(arguments[0], arguments, env) == -1)
		{
			perror("mmmm");
			exit(0);
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
	//COMMON
	envstring.push_back("SERVER_ADDR=127.0.0.1");
	envstring.push_back("SERVER_PORT=" + to_string(port));
	envstring.push_back("SERVER_NAME=" + requests.host);
	envstring.push_back("SERVER_PROTOCOL=HTTP/1.1");

	envstring.push_back("SCRIPT_FILENAME=" + requests.file);
	envstring.push_back("PATH_INFO=" + requests.path_info);
	envstring.push_back("REDIRECT_STATUS=200");
	//envstring.push_back("CONTENT_TYPE=" + requests.content_type);
	envstring.push_back("CONTENT_TYPE=" + requests.headers["Content-Type"]);
	envstring.push_back("CONTENT_LENGTH=" + to_string(requests.content.size()));
	envstring.push_back("QUERY_STRING=" + requests.query);
	strtoupper(requests.type);
	envstring.push_back("REQUEST_METHOD=" + requests.type);
	strtolower(requests.type);
	envstring.push_back("ORIG_PATH_INFO=" + requests.uri);
	envstring.push_back("REQUEST_URI=" + requests.uri);
	envstring.push_back("HTTP_COOKIE=" + requests.headers["Cookie"]);
	//envstring.push_back("SCRIPT_NAME=" + requests.file);
	
	vector<char *> env;
	for (size_t i = 0; i < envstring.size(); i++)
		env.push_back((char *)envstring[i].c_str());
	env.push_back(0);

	//POST VARS
	pipe(post);
	printr(requests.content);
	cout << requests.headers["Content-Type"] << endl;
	write(post[1], requests.content.c_str(), requests.content.size());
	close(post[1]);
	pipe(fd);

	int pid = exec(arguments, &env[0], post[0], fd[1]);

	close(fd[1]);
	close(post[0]);

	response.late.pid = pid;
	response.late.fd = fd[0];
	response.late.waiting = true;
	response.late.start = get_time();
}

// string	extract_php(string html)
// {
// 	int start = 0;
// 	while (true)
// 	{
// 		start = html.find("<?php", start);
// 		if (start == -1)
// 			return (html);
// 		int end = html.find("?>", start);
// 		cout << end << endl;
// 		string php = html.substr(start, end - start + 2);
// 		php = exec_php(php);
// 		html.replace(start, end - start + 2, php);
// 		start = end;
// 	}
// }

	// env.push_back((char *)"SERVER_PROTOCOL=HTTP/1.1");
	// env.push_back((char *)"REQUEST_METHOD=POST");
	// env.push_back((char *)"CONTENT_TYPE=application/x-www-form-urlencoded");
	// env.push_back((char *)"CONTENT_LENGTH=21");
	// env.push_back((char *)("SCRIPT_FILENAME=" + requests.file).c_str());
	// env.push_back((char *)("QUERY_STRING=" + requests.query).c_str());
	// env.push_back((char *)("SCRIPT_NAME=" + requests.file).c_str());
	// env.push_back((char *)("REQUEST_URI=" + requests.uri).c_str());
	// env.push_back((char *)("PATH_INFO=" + requests.path_info).c_str());
	// env.push_back(0);
