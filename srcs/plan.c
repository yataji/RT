/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:36:08 by yataji            #+#    #+#             */
/*   Updated: 2021/03/14 00:23:06 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		planiter(t_obj *plan, t_ray ray)
{
	t_vect	oc;
	t_vect	v;
	double	xv;
	double	dv;

	oc = moins(ray.org, plan->center);
	v = normalize(plan->v);
	dv = dot(ray.dir, v);
	xv = dot(oc, v);
	if (dv != 0 && ((dv > 0 && xv < 0) || (dv < 0 && xv > 0)))
	{
		plan->normal = dv > 0 ? multi(v, -1.0) : v;
		return (-xv / dv);
	}
	return (-1);
}

