# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/21 13:58:27 by eweiberl          #+#    #+#              #
#    Updated: 2023/08/19 14:41:39 by eweiberl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SOURCE = main.c
SOURCE += input/get_input.c
SOURCE += utils/ft_atoi.c utils/ft_strlen.c

OBJS = $(SOURCE:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

nflag:
	$(CC) -o $(NAME) $(SOURCE)

debug: $(SOURCE) $(LIBFT)
	$(CC) -g -o $(NAME) $(SOURCE)

bonus: all

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: re all clean