/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:36:08 by yataji            #+#    #+#             */
/*   Updated: 2021/03/10 19:23:05 by yataji           ###   ########.fr       */
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
	if ((t = dot(ray.dir, v)) != 0)
		if (t != (xv = dot(oc, v)))
			return (-xv / t);
	return (-1);
}
