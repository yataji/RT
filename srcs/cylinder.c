/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:43:03 by yataji            #+#    #+#             */
/*   Updated: 2021/03/19 01:09:36 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		print_vect(t_vect v, char *name)
{
	printf("%s: {%lf, %lf, %lf}\n", name, v.x, v.y, v.z);
}

double		cyldintr(t_obj *cyld, t_ray ray)
{
	t_vect	v;
	t_vect	oc;
	t_math	calc;

	oc = moins(ray.org, cyld->center);
	v = normalize(cyld->v);
	v = normalize(rotation_xyz(v, cyld->rot));
	calc.a = dot(ray.dir, ray.dir) - dot(ray.dir, v) * dot(ray.dir, v);
	calc.b = 2 * (dot(ray.dir, oc) - dot(ray.dir, v) * dot(oc, v));
	calc.c = dot(oc, oc) - dot(oc, v) * dot(oc, v) - multidbl(cyld->radius,
			cyld->radius, 1);
	calc.delta = multidbl(calc.b, calc.b, 1) - multidbl(4, calc.a, calc.c);
	return (checkt(calc));
}

t_vect		normcyld(t_ray *ray, t_obj *obj, double t)
{
	double	m;
	t_vect	v;
	t_vect	oc;
	t_vect	norm;

	v = normalize(obj->v);
	v = normalize(rotation_xyz(v, obj->rot));
	ray->hit = plus(ray->org, multi(ray->dir, t));
	oc = moins(ray->org, obj->center);
	m = dot(ray->dir, v) * t + dot(oc, v);
	norm = moins(moins(ray->hit, obj->center), multi(v, m));
	if (dot(norm, ray->dir) > 0)
		norm = multi(norm, -1.0);
	return (normalize(norm));
}
