/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:00:48 by yataji            #+#    #+#             */
/*   Updated: 2021/04/20 11:50:05 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	usage(void)
{
	ft_putendl("usage: ./rtv1 scene/(chose a file .yaml)");
	exit(1);
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
			usage();
		rt = init_list(rt);
		if (parse(&rt) == -1)
		{
			ft_putendl("error parsing");
			ft_free(&rt.obj, &rt.lights, &rt.cam);
			return (0);
		}
		init_sdl(&rt);
		draw(rt);
		loop_program(&rt);
	}
	else
		usage();
	return (0);
}
