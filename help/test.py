# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaud <albaud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 00:51:09 by albaud            #+#    #+#              #
#    Updated: 2023/05/22 20:23:07 by albaud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import requests


my = requests.get("http://localhost:4141/post.html")
his = requests.get("http://localhost:4343/post.html", cookies={
	"session": fjhadjf
})

def comp(a, b):
    if a != b:
        print("A>>>>")
        print(a)
        print("B>>>>")
        print(b)

def comp_request(a, b):
	comp(a.text, b.text)
	comp(a.history, b.history)
	comp(a.cookies, b.cookies)
	comp(a.headers, b.headers)
	comp(a.history, b.history)
	comp(a.status_code, b.status_code)
	comp(a.raw, b.raw)
	comp(a.reason, b.reason)
	comp(a.request, b.request)
comp_request(my, his)
# response = requests.post("http://localhost:4343/")
# print(response.text)
# print(response.status_code)

# response = requests.delete("http://localhost:4343/")
# print(response.text)
# print(response.status_code)
