# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yataji <yataji@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/20 11:57:48 by yataji            #+#    #+#              #
#    Updated: 2021/03/05 13:08:17 by yataji           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
OBJ  = srcs/main.o srcs/math.o srcs/key.o srcs/free.o srcs/init.o srcs/sphere.o srcs/cylinder.o srcs/cone.o srcs/draw.o srcs/plan.o
FLG  = -Wall -Wextra -Werror
INC  = includes/
INCS = includes/rtv1.h


all: $(NAME)

%.o : %.c $(INCS)
	@gcc $(FLG) -o $@ -c $< -I $(INC)
	
$(NAME): $(OBJ) 
	@make -s -C libft
	@make -s -C minilibx_macos
	@gcc $(FLG) minilibx_macos/libmlx.a libft/libft.a $(OBJ) -framework OpenGL -framework AppKit -o $(NAME) -I $(INCS)
	@printf "compilation completed\n"

clean:
	@make -C libft/ clean
	@make -C minilibx_macos/ clean
	@rm -f $(OBJ)
	@printf "clean terminated\n"

fclean: clean
	@make -C libft/ fclean
	@make -C minilibx_macos/ fclean
	@rm -f $(OBJ) $(NAME)
	@printf "clean all\n"

re: fclean all
