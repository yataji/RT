/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:43:03 by yataji            #+#    #+#             */
/*   Updated: 2021/04/23 15:36:48 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	cly_slice(t_obj *cyl, t_ray r, t_sol sol, t_vect sly)
{
	r.hit = plus(r.org, multi(r.dir, sol.tmax));
	if (sol.tmax > 0 && dot(moins(cyl->pos_slice, r.hit), sly) > 0.0)
		return (sol.tmax);
	return (-1);
}

double	lim_cyl_y(t_obj *cyl, t_vect hit, double tmax, t_ray r)
{
	t_vect		hit2;

	if (hit.y > cyl->center.y + cyl->size / 2
		|| hit.y < cyl->center.y - cyl->size / 2)
	{
		r.hit = plus(r.org, multi(r.dir, tmax));
		hit2 = moins(r.hit, cyl->center);
		if (hit2.y >= cyl->center.y + cyl->size / 2
			|| hit2.y <= cyl->center.y - cyl->size / 2)
			return (-1);
	}
	return (tmax);
}

double	lim_cyl_x(t_obj *cyl, t_vect hit, double tmax, t_ray r)
{
	t_vect		hit2;

	if (hit.x > cyl->center.x + cyl->size / 2
		|| hit.x < cyl->center.x - cyl->size / 2)
	{
		r.hit = plus(r.org, multi(r.dir, tmax));
		hit2 = moins(r.hit, cyl->center);
		if (hit2.x >= cyl->center.x + cyl->size / 2
			|| hit2.x <= cyl->center.x - cyl->size / 2)
			return (-1);
	}
	return (tmax);
}

double	lim_cyl_z(t_obj *cyl, t_vect hit, double tmax, t_ray r)
{
	t_vect		hit2;

	if (hit.z > cyl->center.z + cyl->size / 2
		|| hit.z < cyl->center.z - cyl->size / 2)
	{
		r.hit = plus(r.org, multi(r.dir, tmax));
		hit2 = moins(r.hit, cyl->center);
		if (hit2.z >= cyl->center.z + cyl->size / 2
			|| hit2.z <= cyl->center.z - cyl->size / 2)
			return (-1);
	}
	return (tmax);
}

double	limeted_cly(t_obj *cyl, t_ray r, t_sol sol)
{
	t_vect	up;
	t_vect	hit;
	t_vect	hit2;
	t_vect	sly;
	int		is;

	sly = cyl->slice;
	if (!sly.x && !sly.y && !sly.z)
		is = 0;
	else
		is = 1;
	if (is == 1 && dot(moins(cyl->pos_slice, r.hit), sly) < 0.0)
		return (cly_slice(cyl, r, sol, sly));
	hit = moins(r.hit, cyl->center);
	if (cyl->v.y == 1)
		return (lim_cyl_y(cyl, hit, sol.tmax, r));
	if (cyl->v.x == 1)
		return (lim_cyl_x(cyl, hit, sol.tmax, r));
	if (cyl->v.z == 1)
		return (lim_cyl_z(cyl, hit, sol.tmax, r));
	return (sol.tmin);
}
