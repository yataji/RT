/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:36:08 by yataji            #+#    #+#             */
/*   Updated: 2021/04/18 15:11:00 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			plan_slice(t_obj *pln, t_ray r, double t)
{
	int 	is;

	if (!pln->slice.x && !pln->slice.y && !pln->slice.z)
		is = 0;
	else
		is = 1;
	if (is == 1 && dot(moins(pln->pos_slice, r.hit), pln->slice) <= 0.0)
			return (-1);
	return (t);
}
double			limeted_plan(t_obj *pln, t_ray r, double t)
{
	t_vect		hit;

	hit = moins(r.hit, pln->center);
	if (t == -1)
		return (-1);
	if ((hit.y > pln->center.y + pln->size/2 ||
		hit.y < pln->center.y - pln->size/2) && pln->v.y == 0)
		return (-1);
	if ((hit.x > pln->center.x + pln->size/2 ||
		hit.x < pln->center.x - pln->size/2) && pln->v.x == 0)
		return (-1);
	if ((hit.z > pln->center.z + pln->size/2 ||
		hit.z < pln->center.z - pln->size/2) && pln->v.z == 0)
		return (-1);
	return (t);
}


double	planiter(t_obj *plan, t_ray ray)
{
	t_vect	oc;
	t_vect	v;
	double	xv;
	double	dv;
	double	t;

	t = -1;
	oc = moins(ray.org, plan->center);
	v = normalize(plan->v);
	v = rotation_xyz(v, plan->rot);
	dv = dot(ray.dir, v);
	xv = dot(oc, v);
	if (dv != 0 && ((dv > 0 && xv < 0) || (dv < 0 && xv > 0)))
	{
		if (dv > 0)
			plan->normal = multi(v, -1.0);
		else
			plan->normal = v;
		t = -xv / dv;
	}
	ray.hit = plus(ray.org, multi(ray.dir, t));
	t = plan_slice(plan, ray, t);
	if (plan->size != 0)
		t = limeted_plan(plan, ray, t);
	return (t);
}
