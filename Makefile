# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsekiguc <tsekiguc@student.42tokyo.jp      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 09:43:13 by tsekiguc          #+#    #+#              #
#    Updated: 2021/11/04 11:02:03 by tsekiguc         ###   ########.fr        #
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
INCLUDE			=	-I./libft
LIB				=	-L./libft -lft

RM				=	rm -f

.SUFFIXES		:
.SUFFIXES		:	.c .o

.PHONY			:	all clean fclean re

all				:	$(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME)	:	$(SERVER_OBJS)
					make -C libft
					$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIB) -o $@

$(CLIENT_NAME)	:	$(CLIENT_OBJS)
					make -C libft
					$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIB) -o $@

%.o				:	%.c
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
