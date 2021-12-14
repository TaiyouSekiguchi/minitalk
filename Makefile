# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 09:43:13 by tsekiguc          #+#    #+#              #
#    Updated: 2021/11/11 15:16:58 by tsekiguc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER_NAME		=	server
SERVER_SRCS		=	server_main.c\
					server_buf.c\
					server_error.c\
					server_recieve_signal.c
SERVER_OBJS		=	$(SERVER_SRCS:.c=.o)

CLIENT_NAME		=	client
CLIENT_SRCS		=	client_main.c
CLIENT_OBJS		=	$(CLIENT_SRCS:.c=.o)

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
INCLUDE			=	-I include
LIB				=	-L./libft -lft

RM				=	rm -f

.PHONY			:	all clean fclean re

vpath %.c srcs
vpath %.h include

all				:	$(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME)	:	$(SERVER_OBJS)
					make -C libft
					$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIB) -o $@

$(CLIENT_NAME)	:	$(CLIENT_OBJS)
					make -C libft
					$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIB) -o $@

$(SERVER_OBJS)	:	%.o	:	%.c include/server.h
					$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(CLIENT_OBJS)	:	%.o	:	%.c include/client.h
					$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean			:
					make clean -C libft
					$(RM) $(SERVER_OBJS)
					$(RM) $(CLIENT_OBJS)

fclean			:
					make fclean -C libft
					$(RM) $(SERVER_OBJS) $(SERVER_NAME) 
					$(RM) $(CLIENT_OBJS) $(CLIENT_NAME) 

re				:	fclean all
