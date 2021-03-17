/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:18:10 by yataji            #+#    #+#             */
/*   Updated: 2021/03/17 19:35:42 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int shadow(t_rtv1 *rt, t_obj *close)
{
	t_obj *tmp;
	t_var v;
	t_ray shadow_r;
	double dist;

	tmp = rt->obj;
	shadow_r.org = rt->lights->pos;
	dist = dot(moins(rt->ray.hit, rt->lights->pos),
			   moins(rt->ray.hit, rt->lights->pos));
	shadow_r.dir = normalize(moins(rt->ray.hit, rt->lights->pos));
	while (tmp)
	{
		if (tmp != close && ((v.near = intersect(tmp, shadow_r)) > 0 &&
							 v.near > 0))
		{
			v.t = v.near;
			if (dot(multi(shadow_r.dir, v.t), multi(shadow_r.dir, v.t)) < dist)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

t_color diffuspclr(t_rtv1 *rt, t_obj *close, t_lights *lights, int shad)
{
	double dot1;
	t_vect lightdir;
	t_vect reflect;
	t_color c;

	c = (t_color){0, 0, 0};
	lightdir = normalize(moins(lights->pos, rt->ray.hit));
	dot1 = dot(close->normal, lightdir);
	reflect = normalize(moins(lightdir, multi(close->normal, 2 * dot1)));
	if (dot1 > 0 && shad)
		c = multi_color(close->color, dot1 * lights->intensity / 100.0);
	if (shad && (dot1 = dot(reflect,
							normalize(moins(rt->ray.hit, rt->ray.org)))) > 0)
		c = add_color(c, multi_color(lights->color, powf(dot1, 80)));
	return (c);
}

int color(t_rtv1 *rt, t_obj *close, t_lights *lights)
{
	t_vect lightdir;
	t_color c;
	t_color ret;
	int shad;

	rt->color = 0;
	rt->ptr = (unsigned char *)&rt->color;
	ret = multi(close->color, 0.2);
	c = (t_color){0, 0, 0};
	rt->tmpl = lights;
	while (rt->tmpl)
	{
		lightdir = normalize(moins(rt->tmpl->pos, rt->ray.hit));
		rt->dot1 = dot(close->normal, lightdir);
		shad = shadow(rt, close);
		c = diffuspclr(rt, close, rt->tmpl, shad);
		ret = add_color(ret, multi(c, shad));
		rt->tmpl = rt->tmpl->next;
	}
	rt->ptr[2] = ret.x;
	rt->ptr[1] = ret.y;
	rt->ptr[0] = ret.z;
	rt->ptr[3] = 0;
	return (rt->color);
}

void draw2(t_var v, t_obj *close, t_rtv1 rt, t_obj *tmp)
{
	while (tmp)
	{
		if ((v.near = intersect(tmp, rt.ray)) > 0 &&
			((v.near < v.t && v.t > 0) || (v.near > v.t && v.t < 0)))
		{
			close = tmp;
			v.t = v.near;
		}
		tmp = tmp->next;
	}
	if (v.t > 0 && close)
	{
		setnormal(close, &rt.ray, v.t);
		rt.mlx.dtadd[v.x + v.y * MAXWIDTH] = color(&rt, close, rt.lights);
	}
	else
		rt.mlx.dtadd[v.x + v.y * MAXWIDTH] = 0;
}

void draw(t_rtv1 rt)
{
	t_obj *close;
	t_obj *tmp;
	t_var v;

	v.x = -1;
	v.near = -1.0;
	while (++v.x < MAXWIDTH)
	{
		v.y = -1;
		while (++v.y < MAXHEIGHT)
		{
			rt.ray = initray(rt, v.x, v.y);
			tmp = rt.obj;
			close = NULL;
			v.t = -1;
			draw2(v, close, rt, tmp);
		}
	}
}
