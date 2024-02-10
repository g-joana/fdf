# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgils <jgils@student.42.rio>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 13:12:54 by jgils             #+#    #+#              #
#    Updated: 2024/02/10 04:46:19 by jgils            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror -c
NAME = libft.a
FILES_C = ft_atoi.c ft_strdup.c ft_calloc.c ft_strjoin.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_striteri.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c get_next_line.c ft_strstr.c
FILES_O = $(FILES_C:.c=.o)
BONUS_C = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
BONUS_O = $(BONUS_C:.c=.o)

all: $(NAME)

.c.o:
	cc $(FLAGS) $< -o $@

$(NAME): $(FILES_O)
	ar -rc libft.a $(FILES_O)

bonus: $(BONUS_O) $(FILES_O)
	ar -rc libft.a $(BONUS_O) $(FILES_O)

so:
	cc -nostartfiles -fPIC $(FLAGS) $(FILES_C) $(BONUS_C)
	gcc -nostartfiles -shared -o libft.so $(FILES_O) $(BONUS_O)

exec: $(FILES_C)
	cc -Wall -Wextra -Werror -o -c exec $(FILES_C)

clean:
	rm -rf $(FILES_O) $(BONUS_O)

fclean: clean
	rm -rf $(NAME)

re: fclean all
