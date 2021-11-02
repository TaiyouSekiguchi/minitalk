# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 09:43:13 by tsekiguc          #+#    #+#              #
#    Updated: 2021/11/02 10:47:55 by tsekiguc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER_NAME		=	server
SERVER_SRCS		=	server.c
SERVER_OBJS		=	$(SERVER_SRCS:.c=.o)

CLIENT_NAME		=	client
CLIENT_SRCS		=	client.c
CLIENT_OBJS		=	$(CLIENT_SRCS:.c=.o)

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

RM				=	rm -f

.SUFFIXES		:
.SUFFIXES		:	.c .o

.PHONY			:	all clean fclean re

all				:	$(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME)	:	$(SERVER_OBJS)
					$(CC) $(CFLAGS) $^ -o $@

$(CLIENT_NAME)	:	$(CLIENT_OBJS)
					$(CC) $(CFLAGS) $^ -o $@

%.o				:	%.c
					$(CC) $(CFLAGS) -c $< -o $@

clean			:
					$(RM) $(SERVER_OBJS)
					$(RM) $(CLIENT_OBJS)

fclean			:	clean
					$(RM) $(SERVER_NAME) 
					$(RM) $(CLIENT_NAME) 

re				:	fclean all
