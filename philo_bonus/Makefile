# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 15:37:56 by hkawakit          #+#    #+#              #
#    Updated: 2022/05/22 22:49:05 by hkawakit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus
SRCS	=	main_bonus.c \
			setup_rules_bonus.c \
			utils_bonus.c
OBJS	=	$(SRCS:.c=.o)
CC		=	gcc
CFLAG	=	-Wall -Wextra -Werror -pthread

%.o: %.c
	$(CC) $(CFLAG) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAG) -o $@ $^

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
