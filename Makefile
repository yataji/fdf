# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yataji <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/24 02:55:27 by yataji            #+#    #+#              #
#    Updated: 2019/11/29 19:52:41 by yataji           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf
SRCS= srcs/checksave.c srcs/fonction_utils.c srcs/designe.c srcs/main.c
OBJ= srcs/checksave.o srcs/fonction_utils.o srcs/designe.o srcs/main.o
FLG= -Wall -Wextra -Werror
all: $(NAME) $(OBJ)

$(NAME): $(OBJ)
	@make -s -C libft
	@gcc $(FLG) libft/libft.a $(SRCS) -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -o $(NAME)
%.o : %.c
	@gcc -c -o $@ $<
clean:
	@make -C libft/ clean
	@rm -f $(OBJ)

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)

re: fclean all
