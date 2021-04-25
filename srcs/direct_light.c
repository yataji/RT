/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 15:37:40 by jiqarbac          #+#    #+#             */
/*   Updated: 2021/04/25 13:36:19 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	comp(double x, double y, double z)
{
	if (x <= y)
		return (y);
	if (x >= z)
		return (z);
	return (x);
}

int	light_direct(t_rt *rt, t_obj *close, t_lights *li)
{
	double	cutoff;
	double	outcutoff;
	double	theta;
	double	intensity;

	rt->lights->hit_to_light.dir = moins(li->pos, close->hit);
	cutoff = rt->lights->angle * M_PI / 180;
	outcutoff = (rt->lights->angle + 3) * M_PI / 180;
	theta = dot(normalize(rt->lights->hit_to_light.dir), normalize(rt->lights->pos));
	intensity = comp((theta - outcutoff) / cutoff - outcutoff, 0.0, 1.0);
	return (intensity);
}
