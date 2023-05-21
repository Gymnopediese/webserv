/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   php.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:32:43 by albaud            #+#    #+#             */
/*   Updated: 2023/05/21 01:55:44 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../header.hpp"

string	exec_php(string php)
{
	char* php_executatble = (char*)"/opt/homebrew/bin/php";
	char* const arguments[] = { (char*)php_executatble, (char*)php.c_str(), NULL };
	int pid;
	int	fd[2];
	int	status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		if (execve(php_executatble, arguments, 0) == -1)
			cerr << " aiaii iaiiaiaii ia" << endl;
	}
	wait(&status);
	close(fd[1]);
	char buffer[10000];
	ssize_t bytesRead = read(fd[0], buffer, 10000 - 1);
	buffer[bytesRead] = 0;
	close(fd[0]);
	return (string(buffer));
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
