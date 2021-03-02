/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:56:21 by yataji            #+#    #+#             */
/*   Updated: 2021/03/01 17:12:05 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double coneintr(t_obj *cone, t_ray ray)
{
    t_vect	v;
	t_vect	oc;
	t_math	calc;
    double k;

	oc = moins(ray.org, cone->center);
	v = normalize((t_vect){0, 1, 0});
    k = 25.0 * M_PI / 180.0;
    k = tan(k / 2);
    calc.a = dot(ray.dir, ray.dir) - (1 + k * k) * multidbl(dot(ray.dir, v), dot(ray.dir, v), 1);
    calc.b = 2 * dot(ray.dir, oc) - (1 + k * k) * multidbl(dot(ray.dir, v), dot(oc, v), 1);
    calc.c = dot(oc, oc) - (1 + k + k) * multidbl(dot(oc, v), dot(oc, v), 1);
    calc.delta = multidbl(calc.b, calc.b, 1) - multidbl(4, calc.a, calc.c);
    return (checkt(calc));
}

t_vect  normcone(t_ray *ray, t_obj *obj, double t)
{
    double  k;
    double  m;
    t_vect  v;
    t_vect  oc;
    t_vect  norm;

    k = 25.0 * M_PI / 180.0;
    k = tan(k / 2.0);
    v = normalize((t_vect){0, 1, 0});
	ray->hit = plus(ray->org, multi(ray->dir, t));
    oc = moins(ray->org, obj->center);
    m = dot(ray->dir, v) * t + dot(oc, v);
    norm = moins(moins(ray->hit, obj->center), multi(v, (1 + k * k) * m));
    if (dot(norm, ray->dir) > 0)
		norm = multi(norm, -1.0);
    return (normalize(norm));
}