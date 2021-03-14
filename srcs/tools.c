/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:44:50 by yataji            #+#    #+#             */
/*   Updated: 2021/03/14 00:18:31 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		checkt(t_math calc)
{
	double	t1;
	double	t2;

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

double		intersect(t_obj *object, t_ray ray)
{
	if (object->type == CYLINDER)
		return (cyldintr(object, ray));
	if (object->type == SPHERE)
		return (sphrintr(object, ray));
	if (object->type == CONE)
		return (coneintr(object, ray));
	if (object->type == PLAN)
		return (planiter(object, ray));
	return (-1);
}

t_vect		normalize(t_vect v2)
{
	double	v;
	t_vect	v1;

	v = sqrtf((v2.x * v2.x) + (v2.y * v2.y) + (v2.z * v2.z));
	v1.x = v2.x / v;
	v1.y = v2.y / v;
	v1.z = v2.z / v;
	return (v1);
}

void		setnormal(t_obj *close, t_ray *ray, double t)
{
	if (close->type == SPHERE)
		close->normal = normsphr(ray, close, t);
	else if (close->type == CYLINDER)
		close->normal = normcyld(ray, close, t);
	else if (close->type == CONE)
		close->normal = normcone(ray, close, t);
	else if (close->type == PLAN)
		ray->hit = plus(ray->org, multi(ray->dir, t));
}
