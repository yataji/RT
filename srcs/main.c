/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:00:48 by yataji            #+#    #+#             */
/*   Updated: 2021/04/20 02:18:15 by yataji           ###   ########.fr       */
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
		t_obj *l;
		l = rt.obj;
		if (!l)
			return (0);
		printf ("texture: %s\npos_texture: %f:%f:%f\nslice: %f\npos_slice: %f:%f:%f\ncenter: %f:%f:%f\ntrs: %f:%f:%f\nradius: %f\ncolor: %f:%f:%f\nrefl: %d\nrefr: %d\nmatter: %d\nper_refr: %d\nneg_obj: %d\n", l->texture, l->pos_texture.x, l->pos_texture.y, l->pos_texture.z, l->slice, l->pos_slice.x, l->pos_slice.y, l->pos_slice.y, l->center.x, l->center.y, l->center.z, l->trs.x, l->trs.y, l->trs.z, l->radius, l->color.x, l->color.y, l->color.z, l->refl, l->refr, l->matter, l->per_refr, l->neg_obj);
		exit(0);
		init_sdl(&rt);
		draw(rt);
		loop_program(&rt);
	}
	else
		usage();
	return (0);
}
