# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/21 13:58:27 by eweiberl          #+#    #+#              #
#    Updated: 2023/09/25 21:13:50 by eweiberl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -fsanitize=thread

SOURCE = main.c
SOURCE += input/get_input.c
SOURCE += utils/ft_atoi.c utils/ft_strlen.c utils/ft_calloc.c
SOURCE += philos/init_philos.c philos/exec_philo.c philos/simulation.c philos/philo_utils.c
SOURCE += time/get_time.c

OBJS = $(SOURCE:.c=.o)

all: $(NAME)

dataraces: CFLAGS += -fsanitize=thread
dataraces: re

debian: CFLAGS += -pthread
debian: re

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

nflag: CFLAGS =
nflag: re

debug: $(SOURCE)
	$(CC) -g -arch x86_64 -o $(NAME) $(SOURCE)

bonus: all

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: re all clean