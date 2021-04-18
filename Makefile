# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yataji <yataji@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/20 11:57:48 by yataji            #+#    #+#              #
#    Updated: 2021/04/17 23:37:02 by yataji           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
OBJSRC  = srcs/main.o srcs/math.o srcs/mathnorm.o srcs/camera.o srcs/tools.o srcs/free.o srcs/sphere.o srcs/cylinder.o srcs/cone.o srcs/draw.o srcs/plane.o srcs/rotation.o srcs/sdl/sdl.o
OBJPARSE = srcs/parse/parse.o srcs/parse/camera.o srcs/parse/lights.o srcs/parse/obj_cone.o srcs/parse/obj_cylinder.o srcs/parse/obj_plane.o srcs/parse/obj_sphere.o srcs/parse/parse_check.o srcs/parse/stock.o srcs/parse/init_parce.o
OBJS = $(OBJSRC) $(OBJPARSE)
FLG  = -Wall -Wextra -Werror
INC  = includes/
INCS = includes/rt.h
LIBFT = libft/libft.a
SDL = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image 
INCLUDE	= -I /Users/$$USER/.brew/Cellar/sdl2/2.0.14_1/include -I /Users/$$USER/.brew/Cellar/sdl2_image/2.0.5/include 
LIB = -L /Users/$$USER/.brew/Cellar/sdl2/2.0.14_1/lib -L /Users/$$USER/.brew/Cellar/sdl2_image/2.0.5/lib

all: $(NAME)

%.o : %.c $(INCS)
	@gcc $(FLG) -o $@ -c $< -I $(INC)
	
$(NAME): $(OBJS)
	@make -s -C libft
	@gcc $(FLG) $(LIBFT) $(OBJS) $(SDL) $(INCLUDE) $(LIB) -o $(NAME) -I $(INCS)
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
