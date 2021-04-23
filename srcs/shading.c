/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:46:21 by jiqarbac          #+#    #+#             */
/*   Updated: 2021/04/23 16:35:04 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	shadow(t_rt *rt, t_lights *lights, t_obj *close)
{
	t_obj		*tmpo;
	t_var		v;
	t_ray		shadow_r;
	t_vect		dirvect;
	double		dist;

	tmpo = rt->obj;
	shadow_r.org = lights->pos;
	dirvect = moins(rt->ray.hit, lights->pos);
	dist = dot(dirvect, dirvect);
	shadow_r.dir = normalize(dirvect);
	while (tmpo)
	{
		if (tmpo->neg_obj == 0)
			v.t = intersect(tmpo, shadow_r) + 0.01;
		if (tmpo != close && v.t > 0)
		{
			if (dot(multi(shadow_r.dir, v.t),
					multi(shadow_r.dir, v.t)) < dist)
				return (0);
		}
		tmpo = tmpo->next;
	}
	return (1);
}

t_color	diffuspclr(t_ray ray, t_obj *close, t_lights *lights)
{
	double		dot1;
	t_vect		lightdir;
	t_vect		reflect;
	t_color		c;

	c = (t_color){0, 0, 0};
	lightdir = normalize(moins(lights->pos, ray.hit));
	dot1 = dot(close->normal, lightdir);
	if (dot1 > 0)
	{
		c = multi_tcolor(close->color, multi_color(lights->color, 1.0 / 255));
		c = multi_color(c, dot1 * lights->intensity / 100.0);
	}
	reflect = normalize(moins(lightdir, multi(close->normal, 2 * dot1)));
	dot1 = dot(reflect, normalize(moins(ray.hit, ray.org)));
	if (dot1 > 0)
		c = add_color(c, multi_color(lights->color, powf(dot1, 100)
					* lights->intensity / 100.0));
	return (c);
}

t_color	refl_refr(t_rt *rt, t_obj *close, t_lights *l, t_ray rayor)
{
	t_obj	*closenew;
	t_ray	ray;
	t_var	v;
	double	t;

	rt->tmpo = rt->obj;
	if (!close || !close->refl)
		return ((t_color){0, 0, 0});
	if (close->refl)
		ray = initrayrfl(rt, rayor, close);
	if (close->refr)
		ray = initrayrfr(rt, rayor, close);
	v.near = -1.0;
	closenew = NULL;
	while (rt->tmpo)
	{
		if (rt->tmpo != close)
		{
			t = intersect(rt->tmpo, ray);
			if ((t < v.near && t > 0) || (t > v.near && v.near < 0))
			{
				closenew = rt->tmpo;
				v.near = t;
			}
		}
		rt->tmpo = rt->tmpo->next;
	}
	ray.hit = plus(ray.org, multi(ray.dir, v.near));
	if (closenew && ft_strcmp(closenew->texture, ".") != 0)
		texture(closenew, ray.hit);
	if (!closenew)
		return ((t_color){0, 0, 0});
	if (closenew->refl || closenew->refr)
		refl_refr(rt, closenew, l, ray);
	setnormal(closenew, &ray, v.near);
	return (diffuspclr(ray, closenew, l));
}
