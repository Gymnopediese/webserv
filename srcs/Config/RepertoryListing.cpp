/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RepertoryListing.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:24:37 by albaud            #+#    #+#             */
/*   Updated: 2023/05/29 23:48:31 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

#ifndef LISTING
#define LISTING "<html>\
<head>\
    <title>Directory Listing</title>\
    <style>\
        body {\
            font-family: Arial, sans-serif;\
            background-color: #f7f7f7;\
            margin: 0;\
            padding: 20px;\
        }\
\
        h1 {\
            color: #333;\
            margin-bottom: 20px;\
        }\
\
        .file-listing {\
            background-color: #fff;\
            border: 1px solid #ccc;\
            border-radius: 5px;\
            padding: 10px;\
        }\
\
        .file-listing a {\
            display: block;\
            color: #333;\
            text-decoration: none;\
            margin-bottom: 5px;\
            transition: color 0.3s;\
        }\
\
        .file-listing a:hover {\
            color: #e67e22;\
        }\
    </style>\
</head>\
<body>\
    <h1>Directory Listing</h1>\
\
    <div class=\"file-listing\">"
#endif


string	repertory_listing(string directoryPath)
{
	stringstream	htmlFile;
	DIR* dir;
    struct dirent* entry;

    // Open the directory
    if ((dir = opendir(directoryPath.c_str())) != NULL)
	{
        htmlFile << LISTING;

        // Iterate over the files and directories
        while ((entry = readdir(dir)) != NULL) {
            std::string name = entry->d_name;

            // Ignore hidden files and special directories (. and ..)
            if (name[0] == '.') {
                continue;
            }

            std::string link = name;
            if (entry->d_type == DT_DIR) {
                link += "/";
            }

            htmlFile << "<a href=\"" << link << "\">" << name << "</a><br>";
        }
        htmlFile << "</div></body></html>";
        closedir(dir);
    }
	else
	{
       throw 403;
    }
	return (htmlFile.str());
}