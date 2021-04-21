/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:56:21 by yataji            #+#    #+#             */
/*   Updated: 2021/04/18 14:53:11 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			cone_slice(t_obj *cone, t_ray r, t_sol sol, t_vect sly)
{
	r.hit = plus(r.org, multi(r.dir, sol.tmax));
	if (sol.tmax > 0 && dot(moins(cone->pos_slice, r.hit), sly) > 0.0)
		return (sol.tmax);
	return (-1);
}

double			lim_cone_y(t_obj *cone, t_vect hit, double tmax, t_ray r)
{
	t_vect		hit2;

	if (hit.y >= cone->center.y + cone->size/2 ||
		hit.y <= cone->center.y - cone->size/2)
	{
		r.hit = plus(r.org, multi(r.dir, tmax));
		hit2 = moins(r.hit, cone->center);
		if (hit2.y >= cone->center.y + cone->size/2 ||
		hit2.y <= cone->center.y - cone->size/2)
			return -1;
	}
	return (tmax);
}


double			lim_cone_x(t_obj *cone, t_vect hit, double tmax, t_ray r)
{
	t_vect		hit2;

	if (hit.x >= cone->center.x + cone->size/2 ||
		hit.x <= cone->center.x - cone->size/2)
	{
		r.hit = plus(r.org, multi(r.dir, tmax));
		hit2 = moins(r.hit, cone->center);
		if (hit2.x >= cone->center.x + cone->size/2 ||
		hit2.x <= cone->center.x - cone->size/2)
			return -1;
	}
	return (tmax);
}
double			lim_cone_z(t_obj *cone, t_vect hit, double tmax, t_ray r)
{
	t_vect		hit2;

	if (hit.z >= cone->center.z + cone->size/2 ||
		hit.z <= cone->center.z - cone->size/2)
	{
		r.hit = plus(r.org, multi(r.dir, tmax));
		hit2 = moins(r.hit, cone->center);
		if (hit2.z >= cone->center.z + cone->size/2 ||
		hit2.z <= cone->center.z - cone->size/2)
			return -1;
	}
	return (tmax);
}

double		limeted_cone(t_obj *cone, t_ray r, t_sol sol)
{
	t_vect		up;
	t_vect		hit;
	t_vect		hit2;
	int		is;

	if (!cone->slice.x && !cone->slice.y && !cone->slice.z)
		is = 0;
	else
		is = 1;
	if (is == 1 && dot(moins(cone->pos_slice, r.hit), cone->slice) <= 0.0)
		return (cone_slice(cone, r, sol, cone->slice));
	hit = moins(r.hit, cone->center);
	if (cone->v.y == 1)
		return (lim_cone_y(cone, hit, sol.tmax, r));
	if (cone->v.x == 1)
		return (lim_cone_x(cone, hit, sol.tmax, r));
	if (cone->v.z == 1)
		return (lim_cone_z(cone, hit, sol.tmax, r));
	return (sol.tmin);
}

double	coneintr(t_obj *cone, t_ray ray)
{
	t_vect	v;
	t_vect	oc;
	t_math	calc;
	double	k;
	t_sol		sol;

	oc = moins(ray.org, cone->center);
	v = normalize(cone->v);
	v = rotation_xyz(v, cone->rot);
	k = cone->angle * M_PI / 180.0;
	k = tan(k / 2.0);
	calc.a = dot(ray.dir, ray.dir) - (1 + k * k)
		* dot(ray.dir, v) * dot(ray.dir, v);
	calc.b = 2 * (dot(ray.dir, oc) - (1 + k * k)
			* dot(ray.dir, v) * dot(oc, v));
	calc.c = dot(oc, oc) - (1 + k * k) * dot(oc, v) * dot(oc, v);
	calc.delta = (calc.b * calc.b) - (4 * calc.a * calc.c);
	sol = check_min_max(calc);
	if (cone->size != 0)
		sol.tmin = limeted_cone(cone, ray, sol);
	return (sol.tmin);
}

t_vect	normcone(t_ray *ray, t_obj *obj, double t)
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
