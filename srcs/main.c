/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:00:48 by yataji            #+#    #+#             */
/*   Updated: 2021/03/12 21:49:02 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			main(int ac, char **av)
{
	t_rtv1	rt;

	if ((rt.fd = open(av[1], O_RDONLY)) && ac != 2)
		return (0); 
	// rt.lights = NULL;
	if (parse(&rt) == -1)
	{
		ft_putendl("error parsing");
		return (0);
	}
// 	printf("x: %lf\ty: %lf\tz: %lf\n", rt.cam.lokat.x, rt.cam.lokat.y, rt.cam.lokat.z);
// printf("x: %lf\ty: %lf\tz: %lf\n", rt.cam.lokfrm.x, rt.cam.lokfrm.y, rt.cam.lokfrm.z);
// while (rt.lights)
// {
// 	// printf("intensity: %lf\tcolor: %d\tpos.x: %lf\tpos.y: %lf\tpos.z: %lf\n", rt.lights->intensity, rt.lights->color, rt.lights->pos.x, rt.lights->pos.y, rt.lights->pos.z);
// 	printf("LIGHTS: intensity: %lf\tcolor.x: %lf\tcolor.y: %lf\tcolor.z: %lf\tpos.x: %lf\tpos.y: %lf\tpos.z: %lf\n", rt.lights->intensity, rt.lights->color.x, rt.lights->color.y, rt.lights->color.z, rt.lights->pos.x, rt.lights->pos.y, rt.lights->pos.z);
// 	rt.lights = rt.lights->next;
// }
// while (rt.obj)
// {
// 	printf("OBJECT: center.x: %lf\tcenter.y: %lf\tcenter.z: %lf\tcolor.x: %lf\tcolor.y: %lf\tcolor.z: %lf\tradius: %lf\taxis.x: %lf\taxis.y: %lf\taxis.z: %lf\tangle: %lf\ttype: %d\n", rt.obj->center.x, rt.obj->center.y, rt.obj->center.z, rt.obj->color.x, rt.obj->color.y, rt.obj->color.z, rt.obj->radius, rt.obj->v.x, rt.obj->v.y, rt.obj->v.z, rt.obj->angle, rt.obj->type);
// 	rt.obj = rt.obj->next;
// }
	rt.mlx = init();
	draw(rt);
	mlx_put_image_to_window(rt.mlx.ptr, rt.mlx.win_ptr, rt.mlx.img_ptr, 0, 0);
	mlx_hook(rt.mlx.win_ptr, 2, 0, &keypress, &rt.mlx);
	mlx_loop(rt.mlx.ptr);
	return (0);
}
