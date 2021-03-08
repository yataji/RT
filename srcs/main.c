/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:00:48 by yataji            #+#    #+#             */
/*   Updated: 2021/03/08 19:18:33 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double checkt(t_math calc)
{
	double t1;
	double t2;

	if (calc.delta < 0)
		return (-1);
	else if (calc.delta == 0)
		return (-calc.b / (2 * calc.a));
	t1 = (-calc.b - sqrtf(calc.delta)) / (2 * calc.a);
	t2 = (-calc.b + sqrtf(calc.delta)) / (2 * calc.a);
	if (t1 < t2 && t1 >= 0)
		return (t1);
	else if (t2 >= 0)
		return (t2);
	return (-1);
}

double intersect(t_obj *object, t_ray ray)
{
	if (object->type == SPHERE)
	{

		return (sphrintr(object, ray));
	}
	if (object->type == CYLINDER)
	{

		return (cyldintr(object, ray));
	}
	if (object->type == CONE)
	{

		return (coneintr(object, ray));
	}
	return (-1);
}

t_vect normalize(t_vect v1)
{
	double v;

	v = sqrtf(dot(v1, v1));
	return (multi(v1, 1.0 / v));
}

int main(int ac, char **av)
{
	t_rtv1 rt;
	int fd;

	if ((fd = open(av[1], O_RDONLY)) && ac != 2)
		return (0);
	// rt.obj = (t_obj *)malloc(sizeof(t_obj));
	// rt.obj->type = SPHERE;
	// rt->obj->type = CYLINDER;
	// rt->obj->type = CONE;
	// rt.obj->center = (t_point){350, 350, 220};
	// rt.obj->radius = 50;
	rt.obj = NULL;
	rt.lights = NULL;
	if (parse(&rt, fd) == -1)
	{
		ft_putendl("error parsing");
		return (0);
	}
	// printf("x: %lf\ty: %lf\tz: %lf\n", rt.cam.lokat.x, rt.cam.lokat.y, rt.cam.lokat.z);
	// printf("x: %lf\ty: %lf\tz: %lf\n", rt.cam.lokfrm.x, rt.cam.lokfrm.y, rt.cam.lokfrm.z);
	// while (rt.lights)
	// {
	// 	// printf("intensity: %lf\tcolor: %d\tpos.x: %lf\tpos.y: %lf\tpos.z: %lf\n", rt.lights->intensity, rt.lights->color, rt.lights->pos.x, rt.lights->pos.y, rt.lights->pos.z);
	// 	printf("intensity: %lf\tcolor.x: %lf\tcolor.y: %lf\tcolor.z: %lf\tpos.x: %lf\tpos.y: %lf\tpos.z: %lf\n", rt.lights->intensity, rt.lights->color.x, rt.lights->color.y, rt.lights->color.z, rt.lights->pos.x, rt.lights->pos.y, rt.lights->pos.z);
	// 	rt.lights = rt.lights->next;
	// }
	// while (rt.obj)
	// {
	// 	printf("center.x: %lf\tcenter.y: %lf\tcenter.z: %lf\tcolor.x: %lf\tcolor.y: %lf\tcolor.z: %lf\tradius: %lf\taxis.x: %lf\taxis.y: %lf\taxis.z: %lf\tangle: %lf\ttype: %d\n", rt.obj->center.x, rt.obj->center.y, rt.obj->center.z, rt.obj->color.x, rt.obj->color.y, rt.obj->color.z, rt.obj->radius, rt.obj->v.x, rt.obj->v.y, rt.obj->v.z, rt.obj->angle, rt.obj->type);
	// 	rt.obj = rt.obj->next;
	// }
	rt.mlx = init();
	draw(rt);
	mlx_hook(rt.mlx.win_ptr, 2, 0, &keypress, &rt.mlx);
	mlx_loop(rt.mlx.ptr);
	return (0);
}

// int main(/*int ac, char **av*/)
// {
// 	t_rtv1 rt;
// 	// int		fd;

// 	// if ((fd = open(av[1], O_RDONLY)) && ac != 2)
// 	// 	return (0);
// 	rt.obj = (t_obj *)malloc(sizeof(t_obj));
// 	// rt.obj->type = SPHERE;
// 	// rt.obj->type = CYLINDER;
// 	rt.obj->type = CONE;
// 	rt.obj->center = (t_point){350, 350, 220};
// 	rt.obj->radius = 50;
// 	rt.obj->next = NULL;
// 	rt = init();
// 	// if (parse(&rt, fd) == -1)
// 	// {
// 	// 	ft_putendl("error parsing");
// 	// 	return (0);
// 	// }
// 	// printf("x: %lf\ty: %lf\tz: %lf\n", rt.cam.lokat.x, rt.cam.lokat.y, rt.cam.lokat.z);
// 	// printf("x: %lf\ty: %lf\tz: %lf\n", rt.cam.lokfrm.x, rt.cam.lokfrm.y, rt.cam.lokfrm.z);
// 	// while (rt.lights)
// 	// {
// 	// 	// printf("intensity: %lf\tcolor: %d\tpos.x: %lf\tpos.y: %lf\tpos.z: %lf\n", rt.lights->intensity, rt.lights->color, rt.lights->pos.x, rt.lights->pos.y, rt.lights->pos.z);
// 	// 	printf("intensity: %lf\tcolor.x: %lf\tcolor.y: %lf\tcolor.z: %lf\tpos.x: %lf\tpos.y: %lf\tpos.z: %lf\n", rt.lights->intensity, rt.lights->color.x, rt.lights->color.y, rt.lights->color.z, rt.lights->pos.x, rt.lights->pos.y, rt.lights->pos.z);
// 	// 	rt.lights = rt.lights->next;
// 	// }
// 	// while (rt.obj)
// 	// {
// 	// 	printf("center.x: %lf\tcenter.y: %lf\tcenter.z: %lf\tcolor.x: %lf\tcolor.y: %lf\tcolor.z: %lf\tradius: %lf\taxis.x: %lf\taxis.y: %lf\taxis.z: %lf\tangle: %lf\ttype: %d\n", rt.obj->center.x, rt.obj->center.y, rt.obj->center.z, rt.obj->color.x, rt.obj->color.y, rt.obj->color.z, rt.obj->radius, rt.obj->v.x, rt.obj->v.y, rt.obj->v.z, rt.obj->angle, rt.obj->type);
// 	// 	rt.obj = rt.obj->next;
// 	// }
// 	// printf("%d\n", rt.obj->type);
// 	draw(rt);
// 	mlx_hook(rt.mlx.win_ptr, 2, 0, &keypress, &rt.mlx);
// 	mlx_loop(rt.mlx.ptr);
// 	return (0);
// }
