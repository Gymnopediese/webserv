/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:17:02 by albaud            #+#    #+#             */
/*   Updated: 2023/05/21 01:56:09 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.hpp"

void	create_file(string filename, string content)
{
	std::ofstream file(filename);
	if (file.is_open()) {
		file << content;
		file.close();
	} else {
		std::cerr << "Unable to open file for writing" << std::endl;
	}
}

void append_file(const std::string& filename, const std::string& content) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << content;
        file.close();
        std::cout << "Text successfully appended to the file." << std::endl;
    } else {
        std::cout << "Unable to open the file." << std::endl;
    }
}


string file_to_str(string filename)
{
    std::ifstream file(filename);
    std::ostringstream contentStream;
    contentStream << file.rdbuf(); // Read the file content into the stream
    std::string fileContent = contentStream.str(); // Get the string from the stream
    file.close();
    return fileContent;
}

bool file_exist(const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}