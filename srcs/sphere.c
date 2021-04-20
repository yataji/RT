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

double			sph_slice(t_obj *sph, t_ray r, t_sol sol, t_vect sly)
{
	r.hit = plus(r.org, multi(r.dir, sol.tmax));
	if (sol.tmax > 0 && dot(moins(sph->pos_slice, r.hit), sly) > 0.0)
		return (sol.tmax);
	return (-1);
}

double			limeted_sph(t_obj *sph, t_ray r, t_sol sol)
{
	t_vect	sly;
	int		is;

	sly = sph->slice;
	if (!sly.x && !sly.y && !sly.z)
		is = 0;
	else
		is = 1;
	if (is == 1 && dot(moins(sph->pos_slice, r.hit), sly) <= 0.0)
	{
		r.hit = plus(r.org, multi(r.dir, sol.tmax));
		if (sol.tmax > 0 && dot(moins(sph->pos_slice, r.hit), sly) > 0.0)
			return (sol.tmax);
	}
	return (-1);
}

double	sphrintr(t_obj *sphere, t_ray ray)
{
	t_vect	oc;
	t_math	calc;
	t_sol 	sol;

	oc = moins(ray.org, sphere->center);
	calc.a = dot(ray.dir, ray.dir);
	calc.b = 2 * dot(ray.dir, oc);
	calc.c = dot(oc, oc) - (sphere->radius * sphere->radius);
	calc.delta = (calc.b * calc.b) - (4 * calc.a * calc.c);
	sol = check_min_max(calc);
	if (sphere->slice.x != 0 || sphere->slice.y != 0 || sphere->slice.z != 0)
		return (limeted_sph(sphere, ray, sol));
	return(sol.tmin);
}

t_vect	normsphr(t_ray *ray, t_obj *obj, double t)
{
	t_vect	norm;

	ray->hit = plus(ray->org, multi(ray->dir, t));
	norm = moins(ray->hit, obj->center);
	return (normalize(norm));
}
