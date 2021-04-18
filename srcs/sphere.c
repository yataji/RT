/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:27:45 by yataji            #+#    #+#             */
/*   Updated: 2021/04/18 14:48:55 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_sol	sphrintr(t_obj *sphere, t_ray ray)
{
	t_vect	oc;
	t_math	calc;

	oc = moins(ray.org, sphere->center);
	calc.a = dot(ray.dir, ray.dir);
	calc.b = 2 * dot(ray.dir, oc);
	calc.c = dot(oc, oc) - (sphere->radius * sphere->radius);
	calc.delta = (calc.b * calc.b) - (4 * calc.a * calc.c);
	return (checkt(calc));
}

t_vect	normsphr(t_ray *ray, t_obj *obj, double t)
{
	t_vect	norm;

	ray->hit = plus(ray->org, multi(ray->dir, t));
	norm = moins(ray->hit, obj->center);
	return (normalize(norm));
}
