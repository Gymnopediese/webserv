/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserError.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:44:01 by albaud            #+#    #+#             */
/*   Updated: 2023/05/22 17:55:42 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

void	syntax_error(string message, int line)
{
	std::cerr << "Webserv: Syntax Error: line " << line + 1<< ": " << message << endl;
	exit(1);
}

void	argument_error(string arg, int level, int line)
{
	// string *a[] = 
	// {
	// 	(string []){
	// 		"conf",
	// 	},
	// 	(string []){
	// 		"port",
	// 		"host",
	// 		"root",
	// 		"client_max_body_size",
	// 		"location",
	// 		"cgi",
	// 		"error",
	// 	},
	// 	(string []){
	// 		"php",
	// 		"python",
	// 		"tryfile",
	// 		"return",
	// 		"alias",
	// 		"autoindex",
	// 		"index",
	// 		"dowload",
	// 		"post_action",
	// 		"allow",
	// 		"deny",
	// 		"types"
	// 	}
	// };
	(void) level;
	// (void)a;
	std::cerr << "Webserv: Syntax Error: line " << line << ": \"" << arg  << "\" not valid"<< endl;
	exit(1);
}