/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:00:48 by yataji            #+#    #+#             */
/*   Updated: 2021/03/01 19:24:30 by yataji           ###   ########.fr       */
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

double	intersect(t_obj *object, t_ray ray)
{
	if (object->type == SPHERE)
		return (sphrintr(object, ray));
	if (object->type == CYLINDER)
		return (cyldintr(object, ray));
	return (-1);
}

t_vect	normalize(t_vect v1)
{
	double v;
	
	v = sqrtf(dot(v1, v1));
	return (multi(v1, 1.0 / v));
}

int main()
{
	t_rtv1 rt;

	rt.obj = (t_obj *)malloc(sizeof(t_obj));
	rt.obj->type = CYLINDER;
	rt.obj->center = (t_point){350, 350, 220};
	rt.obj->radius = 50;
	rt.obj->next = NULL;
	rt.mlx = init();
	drawsphr(rt);
	mlx_hook(rt.mlx.win_ptr, 2, 0, &keypress, &rt.mlx);
	mlx_loop(rt.mlx.ptr);
	return (0);
}
