# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/13 06:40:53 by akhalid           #+#    #+#              #
#    Updated: 2021/06/13 06:45:40 by akhalid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

RM = rm -rf

NAME = pipex

SDIR = ./srcs/

SRC =	pipex.c				\
		pipex_utils.c		\
		ft_split.c			\
		libft.c				\
		

IDIR = ./includes/

CFLAGS = -Wall -Wextra -Werror -g

MLX = -lmlx -framework OpenGL -framework AppKit

SRCS =	$(addprefix $(SDIR), $(SRC)) ./srcs/pipex.c

OBJDIR = ./objs
OBJS =	$(OBJDIR)/*.o

all:	$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -I $(IDIR) $(MLX) $(OBJS) -o $(NAME)

$(OBJS):	$(SRCS)
			@$(CC) -c $(CFLAGS) $(SRCS)
			rm -rf ./objs; mkdir ./objs
			mv *.o $(OBJDIR)

clean:
	$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re:	fclean all

.PHONY:	all, clean, fclean, re, bonus