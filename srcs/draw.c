/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:18:10 by yataji            #+#    #+#             */
/*   Updated: 2021/04/18 16:02:15 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	shadow(t_rt *rt, t_lights *lights, t_obj *close)
{
	t_obj		*tmp;
	t_var		v;
	t_sol		t;
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
		t = intersect(tmp, shadow_r);
		// t.tmin = t.tmin + 0.01;
		if (tmp != close && t.tmin > 0)
		{
			if (dot(multi(shadow_r.dir, v.near),
					multi(shadow_r.dir, v.near)) < dist)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

static t_color	diffuspclr(t_ray ray, t_obj *close, t_lights *lights)
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

t_ray	initmpray(t_ray ray, t_obj *closeobj)
{
	t_ray ret;
	t_vect reflect;
	double dot1;

	ret.org = ray.hit;
	dot1 = dot(closeobj->normal, ray.dir);
	reflect = normalize(moins(ray.dir, multi(closeobj->normal, 2 * dot1)));
	ret.dir = reflect;
	ret.maxrf = ray.maxrf + 1;
	return (ret);
}

t_color		reflection(t_rt *rt, t_obj *close, t_lights *l, t_ray rayor)
{
	// t_color ret;
	t_obj *closenew;
	t_ray ray;
	t_var v;
	t_sol	t;

	rt->tmpo = rt->obj;
	if (!close || !close->ref || rayor.maxrf >= 2)
		return ((t_color){0, 0, 0});
	ray = initmpray(rayor, close);
	v.near = -1.0;
	closenew = NULL;
	while (rt->tmpo)
	{
		if (rt->tmpo != close)
		{
			t = intersect(rt->tmpo, ray);
			if ((t.tmin < v.near && t.tmin > 0) || (t.tmin > v.near && v.near < 0))
			{
				closenew = rt->tmpo;
				v.near = t.tmin;
			}
		}
		rt->tmpo = rt->tmpo->next;
	}
	if (!closenew)
		return ((t_color){0, 0, 0});
	if (closenew->ref)
		reflection(rt, closenew, l, ray);
	setnormal(closenew, &ray, v.near);
	return (diffuspclr(ray, closenew, l));
}

t_color	color(t_rt *rt, t_obj *close, t_lights *lights)
{
	t_color		c;
	t_color		ret;
	int			shad;

	// add textures;
	ret = multi(close->color, 0.1);
	rt->tmpl = lights;
	while (rt->tmpl)
	{
		shad = shadow(rt, rt->tmpl, close);
		if (shad)
			c = diffuspclr(rt->ray, close, rt->tmpl);
		else
			c = (t_color){0, 0, 0};
		//reflection
		if (close->ref)
			c = add_color(reflection(rt, close, rt->tmpl, rt->ray), c);
		ret = add_color(ret, c);
		rt->tmpl = rt->tmpl->next;
	}
	return (ret);
}

void	draw2(t_var v, t_obj *close, t_rt rt, t_obj *tmpo)
{
	t_color col;

	while (tmpo)
	{
		rt.t = intersect(tmpo, rt.ray);
		if ((rt.t.tmin < v.near && rt.t.tmin > 0) || (rt.t.tmin > v.near && v.near < 0))
		{
			close = tmpo;
			v.near = rt.t.tmin;
		}
		tmpo = tmpo->next;
	}
	if (v.near > 0 && close)
	{
		setnormal(close, &rt.ray, v.near);
		col = color(&rt, close, rt.lights);
//		if (col.x > 255 || col.y > 255 || col.z > 255)
//			printf("x= %f\ty= %f\tz= %f\n", col.x, col.y, col.z);
		if (SDL_SetRenderDrawColor(rt.rend, col.x, col.y, col.z, 255) != 0)
				sdl_error("Get color failed");
	}
}

void	draw(t_rt rt)
{
	t_obj		*close;
	t_var		v;

	v.y = -1;
	v.near = -1.0;
	while (++v.y < MAXWIDTH)
	{
		v.x = -1;
		while (++v.x < MAXHEIGHT)
		{
			rt.ray = initray(rt.tmpc, v.y, v.x);
			rt.tmpo = rt.obj;
			close = NULL;
			v.near = -1;
			draw2(v, close, rt, rt.tmpo);
			if (SDL_RenderDrawPoint(rt.rend, v.y, v.x) != 0)
				sdl_error("draw point failed");
		}
	}
}
