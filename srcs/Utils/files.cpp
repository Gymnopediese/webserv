/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:17:02 by albaud            #+#    #+#             */
/*   Updated: 2023/05/29 19:24:28 by albaud           ###   ########.fr       */
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
    return access(name.c_str(), R_OK) == 0 && !dir_exist(name);
}

bool dir_exist(const std::string& name) {
	errno = 0;

	int	fd = open(name.c_str(), O_WRONLY);
	int r = errno;

	close(fd);
    return r == 21;
}