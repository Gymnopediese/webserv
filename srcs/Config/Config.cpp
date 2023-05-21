/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:34:30 by albaud            #+#    #+#             */
/*   Updated: 2023/05/21 01:56:28 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config(vector<string> hostnames, int port, string root) : hostnames(hostnames), port(port), root(root){}
Config::Config() : port(){}
Config::~Config(){}