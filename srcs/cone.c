/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:56:21 by yataji            #+#    #+#             */
/*   Updated: 2021/03/27 16:41:51 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		coneintr(t_obj *cone, t_ray ray)
{
	t_vect	v;
	t_vect	oc;
	t_math	calc;
	double	k;

	oc = moins(ray.org, cone->center);
	v = normalize(cone->v);
	v = rotation_xyz(v, cone->rot);
	k = cone->angle * M_PI / 180.0;
	k = tan(k / 2.0);
	calc.a = dot(ray.dir, ray.dir) - (1 + k * k)* dot(ray.dir, v) * dot(ray.dir, v);
	calc.b = 2 * (dot(ray.dir, oc) - (1 + k * k) * dot(ray.dir, v) * dot(oc, v));
	calc.c = dot(oc, oc) - (1 + k * k) * dot(oc, v) * dot(oc, v);
	calc.delta = (calc.b * calc.b) - (4 * calc.a * calc.c);
	return (checkt(calc));
}

t_vect		normcone(t_ray *ray, t_obj *obj, double t)
{
	double	k;
	double	m;
	t_vect	v;
	t_vect	oc;
	t_vect	norm;

	k = obj->angle * M_PI / 180.0;
	k = tan(k / 2.0);
	v = normalize(obj->v);
	v = rotation_xyz(v, obj->rot);
	ray->hit = plus(ray->org, multi(ray->dir, t));
	oc = moins(ray->org, obj->center);
	m = dot(ray->dir, v) * t + dot(oc, v);
	norm = moins(moins(ray->hit, obj->center), multi(v, (1 + k * k) * m));
	if (dot(norm, ray->dir) > 0)
		norm = multi(norm, -1.0);
	return (normalize(norm));
}
