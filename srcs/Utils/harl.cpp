/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 00:00:23 by albaud            #+#    #+#             */
/*   Updated: 2023/05/30 00:50:45 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.hpp"


void	harl(int mode, string message, string color)
{
	string	headers[] = {"[ DEBUG ]", "[ INFOS ]", "[WARNING]", "[ ERROR ]", "[ FATAL ]",};
	string	colors[] = {RESET, BLUE, YELLOW, RED, RED};
	
	color = (color == "" ? colors[mode] : color);
	if (harl_mode <= mode)
		cout << color << headers[mode] << " " << message << RESET << endl;
	if (mode == FATAL)
		exit(1);
}