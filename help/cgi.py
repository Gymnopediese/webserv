# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    cgi.py                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaud <albaud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/21 13:00:14 by albaud            #+#    #+#              #
#    Updated: 2023/05/21 13:01:58 by albaud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import cgi

# Create an instance of the FieldStorage class to access the POST data
form = cgi.FieldStorage()

# Access the value of a specific POST variable
name = form.getvalue('name')

# Print the value of the 'name' variable
print("Hello, " + name + "!")