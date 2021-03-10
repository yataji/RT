/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:36:08 by yataji            #+#    #+#             */
/*   Updated: 2021/03/10 19:11:59 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		planiter(t_obj *plan, t_ray ray)
{
	t_vect	oc;
	t_vect	v;
	double	t;
	double	xv;

	oc = (t_vect){(ray.org.x - plan->center.x), (ray.org.y - plan->center.y),
			(ray.org.z - plan->center.z)};
	v = normalize(plan->v);
	if ((t = dot(ray.dir, v)) != 0 && t != (xv = dot(oc, v)))
	{
		// printf("%lf\n", -xv / t);
		// exit (0);
		return (-xv / t);
	}
	return (-1);
}

// t_vect		normplan(t_ray *ray, t_obj *obj, double t)
// {
// 	t_vect	norm;

// 	ray->hit = plus(ray->org, multi(ray->dir, t));
// 	norm = moins(ray->hit, obj->center);
// 	return (normalize(norm));
// }