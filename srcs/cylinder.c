/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:43:03 by yataji            #+#    #+#             */
/*   Updated: 2021/03/01 19:35:59 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double cyldintr(t_obj *cyld, t_ray ray)
{
	t_vect	v;
	t_vect	oc;
	t_math	calc;

	oc = moins(ray.org, cyld->center);
	v = (t_vect){0, 1, 0};
	calc.a = dot(ray.dir, ray.dir) - dot(ray.dir, v) * dot(ray.dir, v);
	calc.b = 2 * dot(ray.dir, oc) - dot(ray.dir, v) * dot(oc, v);
	calc.c = dot(oc, oc) - dot(oc, v) * dot(oc, v) - multidbl(cyld->radius, cyld->radius, 1);
	calc.delta = multidbl(calc.b, calc.b, 1) - multidbl(4, calc.a, calc.c);
	return(checkt(calc));
}



t_vect	normcyld(t_ray *ray, t_obj *obj, double t)
{
	t_vect	norm;
	t_vect	v;
	t_vect	oc;
	t_vect	n;
	double	m;

	v = (t_vect){0, 1, 0};
	oc = moins(ray.org, cyld->center);
	ray->hit = plus(ray->org, multi(ray->dir, t));
	m = dot(ray.dir, v) * t + dot(oc, v);
	n = 
	return (n);
}