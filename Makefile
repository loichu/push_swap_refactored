# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhumbert <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/14 17:48:26 by lhumbert          #+#    #+#              #
#    Updated: 2021/10/22 18:47:43 by lhumbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=push_swap

CC=gcc

CFLAGS = -Wall -Wextra -Werror -I.
LDFLAGS = -Llibft -lft

SRCS = main.c errors.c analyze.c

OBJS = $(SRCS:.c=.o)
SORT_OBJ = $(SORT_SRC:.c=.o)

RM = rm -f

all:			$(NAME)

$(NAME):		$(OBJS) $(SORT_OBJ)
			gcc -o $(NAME) $(OBJS) $(SORT_OBJ) $(CFLAGS) $(LDFLAGS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus