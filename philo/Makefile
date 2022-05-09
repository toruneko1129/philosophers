# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 15:37:56 by hkawakit          #+#    #+#              #
#    Updated: 2022/05/09 11:30:38 by hkawakit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
SRCS	=	main.c \
			setup_rules.c \
			utils.c
OBJS	=	$(SRCS:.c=.o)
CC		=	gcc
CFLAG	=	-Wall -Wextra -Werror

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
