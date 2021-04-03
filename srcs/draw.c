/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:18:10 by yataji            #+#    #+#             */
/*   Updated: 2021/04/03 01:36:16 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		shadow(t_rtv1 *rt, t_lights *lights, t_obj *close)
{
	t_obj		*tmp;
	t_var		v;
	t_ray		shadow_r;
	t_vect		dirvect;
	double		dist;

	tmp = rt->obj;
	shadow_r.org = lights->pos;
	dirvect = moins(rt->ray.hit, lights->pos); 
	dist = dot(dirvect, dirvect);
	shadow_r.dir = normalize(dirvect);
	while (tmp)
	{
		if (tmp != close && ((v.near = intersect(tmp, shadow_r) + 0.01) > 0))
		{
			if (dot(multi(shadow_r.dir, v.near), multi(shadow_r.dir, v.near)) < dist)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

static t_color	diffuspclr(t_rtv1 *rt, t_obj *close, t_lights *lights)
{
	double		dot1;
	t_vect		lightdir;
	t_vect		reflect;
	t_color		c;

	c = (t_color){0, 0, 0};
	lightdir = normalize(moins(lights->pos, rt->ray.hit));
	dot1 = dot(close->normal, lightdir);
	if (dot1 > 0)
	{
		c = multi_tcolor(close->color, multi_color(lights->color, 1.0 / 255));
		c = multi_color(c, dot1 * lights->intensity / 100.0);
	}
	reflect = normalize(moins(lightdir, multi(close->normal, 2 * dot1)));
	if ((dot1 = dot(reflect, normalize(moins(rt->ray.hit, rt->ray.org)))) > 0)
		c = add_color(c, multi_color(lights->color, powf(dot1, 100)\
						* lights->intensity / 100.0));
	return (c);
}

static int		color(t_rtv1 *rt, t_obj *close, t_lights *lights)
{
	t_color		c;
	t_color		ret;
	int			shad;

	rt->color = 0;
	rt->ptr = (unsigned char *)&rt->color;
	ret = multi(close->color, 0.1);
	rt->tmpl = lights;
	while (rt->tmpl)
	{
		shad = shadow(rt, rt->tmpl, close);
		c = shad ? diffuspclr(rt, close, rt->tmpl) : (t_color){0, 0, 0};
		ret = add_color(ret, c);
		rt->tmpl = rt->tmpl->next;
	}
	rt->ptr[2] = ret.x;
	rt->ptr[1] = ret.y;
	rt->ptr[0] = ret.z;
	rt->ptr[3] = 0;
	return (rt->color);
}

static void		draw2(t_var v, t_obj *close, t_rtv1 rt, t_obj *tmp)
{
	while (tmp)
	{
		if ((v.t = intersect(tmp, rt.ray)) > 0 &&
			((v.t < v.near && v.t > 0) || (v.t > v.near && v.near < 0)))
		{
			close = tmp;
			v.near = v.t;
		}
		tmp = tmp->next;
	}
	if (v.near > 0 && close)
	{
		setnormal(close, &rt.ray, v.near);
		rt.mlx.dtadd[v.x + v.y * MAXWIDTH] = color(&rt, close, rt.lights);
	}
	else
		rt.mlx.dtadd[v.x + v.y * MAXWIDTH] = 0;
}

void			draw(t_rtv1 rt)
{
	t_obj		*close;
	t_obj		*tmp;
	t_var		v;

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
			v.near = -1;
			draw2(v, close, rt, tmp);
		}
	}
}
