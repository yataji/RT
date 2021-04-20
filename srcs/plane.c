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

double	planiter(t_obj *plan, t_ray ray)
{
	t_vect	oc;
	t_vect	v;
	double	xv;
	double	dv;

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
		return (-xv / dv);
	}
	return (-1);
}
