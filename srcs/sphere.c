/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:27:45 by yataji            #+#    #+#             */
/*   Updated: 2021/03/01 15:40:19 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double sphrintr(t_obj *sphere, t_ray ray)
{
	t_vect oc;
	t_math calc;

	oc = (t_vect){ray.org.x - sphere->center.x, ray.org.y - sphere->center.y, ray.org.z - sphere->center.z};
	calc.a = dot(ray.dir, ray.dir);
	calc.b = 2 * dot(ray.dir, oc);
	calc.c = dot(oc, oc) - multidbl(sphere->radius, sphere->radius, 1);
	calc.delta = multidbl(calc.b, calc.b, 1) - multidbl(4, calc.a, calc.c);
	return (checkt(calc));
}

t_vect	normsphr(t_ray *ray, t_obj *obj, double t)
{
	t_vect	norm;

	ray->hit = plus(ray->org, multi(ray->dir, t));
	norm = moins(ray->hit, obj->center);
	return (normalize(norm));
}
