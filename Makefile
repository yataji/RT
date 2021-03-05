# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yataji <yataji@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/20 11:57:48 by yataji            #+#    #+#              #
#    Updated: 2021/03/01 19:08:05 by yataji           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
OBJ  = srcs/main.o srcs/math.o srcs/key.o srcs/free.o srcs/init.o srcs/sphere.o srcs/cylinder.o
FLG  = -Wall -Wextra -Werror
INC  = includes/
INCS = includes/rtv1.h


all: $(NAME)

%.o : %.c $(INCS)
	@gcc $(FLG) -o $@ -c $< -I $(INC)
	
$(NAME): $(OBJ) 
	@make  -s -C libft
	@gcc $(FLG) libft/libft.a $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME) -I $(INCS)
	@printf "compilation completed\n"

clean:
	@make -C libft/ clean
	@rm -f $(OBJ)
	@printf "clean terminated\n"

fclean: clean
	@make -C libft/ fclean
	@rm -f $(OBJ) $(NAME)
	@printf "clean all\n"

re: fclean all
