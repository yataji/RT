# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yataji <yataji@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/20 11:57:48 by yataji            #+#    #+#              #
#    Updated: 2021/04/04 12:12:10 by yataji           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
OBJSRC  = srcs/main.o srcs/math.o srcs/mathnorm.o srcs/camera.o srcs/key.o srcs/tools.o srcs/free.o srcs/sphere.o srcs/cylinder.o srcs/cone.o srcs/draw.o srcs/plane.o srcs/rotation.o srcs/init_mlx.o
OBJPARSE = srcs/parse/parse.o srcs/parse/camera.o srcs/parse/lights.o srcs/parse/obj_cone.o srcs/parse/obj_cylinder.o srcs/parse/obj_plane.o srcs/parse/obj_sphere.o srcs/parse/parse_check.o srcs/parse/stock.o srcs/parse/init_parce.o
OBJS = $(OBJSRC) $(OBJPARSE)
FLG  = -Wall -Wextra -Werror
INC  = includes/
INCS = includes/rtv1.h

all: $(NAME)

%.o : %.c $(INCS)
	@gcc $(FLG) -o $@ -c $< -I $(INC)
	
$(NAME): $(OBJS)
	@make -s -C libft
	@gcc $(FLG) libft/libft.a $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME) -I $(INCS)
	@printf "compilation completed\n"

clean:
	@make -C libft/ clean
	@rm -f $(OBJS)
	@printf "clean terminated\n"

fclean: clean
	@make -C libft/ fclean
	@rm -f $(OBJS) $(NAME)
	@printf "clean all\n"

re: fclean all
