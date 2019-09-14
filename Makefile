# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/22 14:47:41 by dmlitvin          #+#    #+#              #
#    Updated: 2019/09/13 20:43:04 by dmlitvin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls

CC=gcc

FLAGS=-c -Wall -Wextra -Werror

LIB=libft/libft.a

SRC=compare_by_size.c compare_by_str.c compare_by_time.c error_flag_management.c \
get_rights.c list_work.c main.c print_files.c recursion.c simple_print.c \

SRO=$(SRC:.c=.o)

all: $(LIB) $(NAME)

$(LIB):
	@make -C libft/

$(NAME): ft_ls.h $(SRO)
	@$(CC) -o $(NAME) $(SRO) $(LIB)

$(SRO): $(SRC)
	@$(CC) $(FLAGS) $(SRC)

clean:
	@rm $(SRO)
	@make clean -C libft/

fclean: clean
	@rm -f ft_ls
	@make fclean -C libft/

re: fclean all

.PHONY: all clean fclean
