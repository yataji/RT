/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:00:48 by yataji            #+#    #+#             */
/*   Updated: 2021/03/19 00:38:56 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			main(int ac, char **av)
{
	t_rtv1	rt;

	if ((rt.fd = open(av[1], O_RDONLY)) == -1 || ac != 2)
		return (0);
	if (parse(&rt) == -1)
	{
		ft_putendl("error parsing");
		keypress(35, &rt);
		return (0);
	}

	t_lights *l = rt.lights;
	t_obj *o = rt.obj;
	printf("x: %lf\ty: %lf\tz: %lf\n", rt.cam.lokat.x, rt.cam.lokat.y, rt.cam.lokat.z);
	printf("x: %lf\ty: %lf\tz: %lf\n", rt.cam.lokfrm.x, rt.cam.lokfrm.y, rt.cam.lokfrm.z);
	while (l)
	{
		printf("intensity: %lf\tcolor.x: %lf\tcolor.y: %lf\tcolor.z: %lf\tpos.x: %lf\tpos.y: %lf\tpos.z: %lf\n", l->intensity, l->color.x, l->color.y, l->color.z, l->pos.x, l->pos.y, l->pos.z);
		l = l->next;
	}
	while (o)
	{
		printf("center.x: %lf\tcenter.y: %lf\tcenter.z: %lf\tcolor.x: %lf\tcolor.y: %lf\tcolor.z: %lf\tradius: %lf\taxis.x: %lf\taxis.y: %lf\taxis.z: %lf\tangle: %lf\ttype: %d\n", o->center.x, o->center.y, o->center.z, o->color.x, o->color.y, o->color.z, o->radius, o->v.x, o->v.y, o->v.z, o->angle, o->type);
		o = o->next;
	}

	rt.mlx = init();
	draw(rt);
	mlx_put_image_to_window(rt.mlx.ptr, rt.mlx.win_ptr, rt.mlx.img_ptr, 0, 0);
	mlx_hook(rt.mlx.win_ptr, 2, 0, &keypress, &rt);
	mlx_hook(rt.mlx.win_ptr, 17, 0, &ft_exit, &rt);
	mlx_loop(rt.mlx.ptr);
	return (0);
}
