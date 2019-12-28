# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yataji <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/24 02:55:27 by yataji            #+#    #+#              #
#    Updated: 2019/12/27 20:47:39 by yataji           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf
SRCS= srcs/checksave.c srcs/fonction_utils.c srcs/designe.c srcs/main.c
FLG= -Wall -Wextra -Werror
INC= includes/

all: $(NAME)

$(NAME): $(SRCS) $(INC)
	@make -s -C libft
	@gcc $(FLG) libft/libft.a $(SRCS) -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@printf "compilation completed\n"

clean:
	@make -C libft/ clean
	@printf "clean terminated\n"

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)
	@printf "clean all\n"

re: fclean all
