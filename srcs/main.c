/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:00:48 by yataji            #+#    #+#             */
/*   Updated: 2021/04/09 14:55:32 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	usage(void)
{
	ft_putendl("usage: ./rtv1 scene/(chose a file .yaml)");
}

int	checknamefl(char *name)
{
	char	*ex;

	ex = ft_strrchr(name, '.');
	if (ex && !ft_strcmp(".yaml", ex))
		return (1);
	return (0);
}

t_rt	init_list(t_rt rt)
{
	rt.obj = NULL;
	rt.lights = NULL;
	rt.cam = NULL;
	return (rt);
}

int	main(int ac, char **av)
{
	t_rt	rt;

	if (ac == 2 && checknamefl(av[1]))
	{
		rt.fd = open(av[1], O_RDONLY);
		if (rt.fd < 3)
			return (0);
		rt = init_list(rt);
		if (parse(&rt) == -1)
		{
			ft_putendl("error parsing");
			ft_free(&rt.obj, &rt.lights, &rt.cam);
			return (0);
		}
		// rt.mlx = init();
		init_sdl(&rt);
		draw(rt);
		loop_program(&rt);
		// mlx_put_image_to_window(rt.mlx.ptr, rt.mlx.win_ptr,
		// 	rt.mlx.img_ptr, 0, 0);
		// mlx_hook(rt.mlx.win_ptr, 2, 0, &keypress, &rt);
		// mlx_hook(rt.mlx.win_ptr, 17, 0, &ft_exit, &rt);
		// mlx_loop(rt.mlx.ptr);
	}
	else
		usage();
	return (0);
}
