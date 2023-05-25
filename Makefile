# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaud <albaud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 14:57:19 by albaud            #+#    #+#              #
#    Updated: 2023/05/24 22:54:36 by albaud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= webserv
MAIN		= $(wildcard srcs/*.cpp srcs/*/*.cpp)
OBJS		= $(patsubst srcs/%.cpp, objs/%.o, $(MAIN))
LIB 		= libs/koflibc/libft.a libs/vector3d/vlib.a
CC			= c++ -g
CFLAGS		= -Wall -Wextra -Werror
SANITIZE	= -fsanitize=address -static-libsan
OBJ_DIR		= objs
SRC_DIR		= srcs


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all		: ${NAME}

$(NAME)	: ${OBJS}
		${CC} ${CFLAGS} ${LIBS} -o ${NAME} ${OBJS}

c		:
		find srcs/*.c srcs/*/*.c | grep -v *vectors* | grep -v *minilibx_macos* | tr '\n' ' ' 

recompile :
	make re -C koflibc
	make re -C minilibx_macos
	make re

clean	:
		rm -rf $(OBJ_DIR)
fclean	:	clean
		rm -f ${NAME} 
re:		fclean all

lclean	: fclean
		rm -f ${LIB}
relib	: lclean all

leak	: fclean ${LIB}
		${CC} ${CFLAGS} ${SANITIZE} ${MINILIBX} -o ${NAME} ${MAIN} ${LIB}

run		: all
		./miniRT rt_files/test.rt

nginxt	:
		nginx -t -c /Users/albaud/Desktop/Coding++/42/rank_05/webserv/hello.conf

nginx	:
		nginx -c /Users/albaud/Desktop/Coding++/42/rank_05/webserv/hello.conf

test	:
		python help/test.py

show	:
		lsof -i4 | grep 4242