/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:00:48 by yataji            #+#    #+#             */
/*   Updated: 2021/04/04 15:43:18 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	usage(void)
{
	ft_putendl("usage: ./rtv1 scene/(chose a file .yaml)");
}

int	checknamefl(char *name)
{
	size_t	len;

	len = ft_strlen(name);
	while (len > 0)
	{
		if (name[len] == '.')
			if (strncmp(name, ".yaml", 5) > 0)
				return (1);
		len--;
	}
	return (0);
}

t_rtv1	init_list(t_rtv1 rt)
{
	rt.obj = NULL;
	rt.lights = NULL;
	rt.cam = NULL;
	return (rt);
}

int	main(int ac, char **av)
{
	t_rtv1	rt;

	if (ac == 2 && checknamefl(av[1]))
	{
		rt.fd = open(av[1], O_RDONLY);
		if (rt.fd < 3 || ac != 2)
			return (0);
		rt = init_list(rt);
		if (parse(&rt) == -1)
		{
			ft_putendl("error parsing");
			ft_free(&rt.obj, &rt.lights, &rt.cam);
			return (0);
		}
		rt.mlx = init();
		draw(rt);
		mlx_put_image_to_window(rt.mlx.ptr, rt.mlx.win_ptr,
			rt.mlx.img_ptr, 0, 0);
		mlx_hook(rt.mlx.win_ptr, 2, 0, &keypress, &rt);
		mlx_hook(rt.mlx.win_ptr, 17, 0, &ft_exit, &rt);
		mlx_loop(rt.mlx.ptr);
	}
	else
		usage();
	return (0);
}
