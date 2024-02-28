# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgils <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 00:04:41 by jgils             #+#    #+#              #
#    Updated: 2024/02/28 00:57:36 by jgils            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf
SRC=*.c
LIBFT=libft/libft.a
MINILIBX=minilibx-linux/libmlx_Linux.a
CC=cc
FLAGS=-Wall -Wextra -Werror -ggdb3 
INCLUDES=-Imlx_linux -lXext -lX11

all: $(NAME)

$(NAME): $(SRC) $(LIBFT) $(MINILIBX)
	$(CC) $(FLAGS) $(SRC) $(LIBFT) $(MINILIBX) $(INCLUDES) -o $(NAME)

$(LIBFT):
	make -C libft/

$(MINILIBX):
	make -C minilibx-linux/

clean:
	make clean -C libft/
	make clean -C minilibx-linux/

fclean:
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all

.PHONY: clean fclean re
