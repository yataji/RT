/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:18:10 by yataji            #+#    #+#             */
/*   Updated: 2021/04/20 02:06:34 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	shadow(t_rt *rt, t_lights *lights, t_obj *close)
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

t_ray	initmpray(t_rt *rt,t_ray ray, t_obj *closeobj)
{
	t_ray ret;
	t_vect reflect;
	double dot1;

	ret.org = ray.hit;
	dot1 = dot(closeobj->normal, ray.dir);
	reflect = normalize(moins(ray.dir, multi(closeobj->normal, 2 * dot1)));
	ret.dir = reflect;
	rt->maxref++;
	return (ret);
}

t_color		reflection(t_rt *rt, t_obj *close, t_lights *l, t_ray rayor)
{
	// t_color ret;
	t_obj *closenew;
	t_ray ray;
	t_var v;
	double	t;

	rt->tmpo = rt->obj;
	if (!close || !close->refl || rt->maxref > 100)
		return ((t_color){0, 0, 0});
	ray = initmpray(rt, rayor, close);
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
		texture(closenew , ray.hit);
	if (!closenew)
		return ((t_color){0, 0, 0});
	if (closenew->refl)
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
	ret = multi(close->color, rt->cam->ambiante);
	if (ft_strcmp(close->texture, ".") != 0)
	{
		texture(close , rt->ray.hit);
		ret = close->color;
	}
	rt->tmpl = lights;
	while (rt->tmpl)
	{
		shad = shadow(rt, rt->tmpl, close);
		if (shad)
			c = diffuspclr(rt->ray, close, rt->tmpl);
		else
			c = (t_color){0, 0, 0};
		//reflection
		// printf("max= %d\n", rt->ray.maxrf);
		rt->maxref = 0;
		if (close->refl)
			c = add_color(reflection(rt, close, rt->tmpl, rt->ray), c);
		ret = add_color(ret, c);
		rt->tmpl = rt->tmpl->next;
	}
	return (ret);
}

void	draw2(t_var v, t_obj *close, t_rt rt, t_obj *tmpo)
{
	t_color col;

	col = (t_color){0, 0, 0};
	while (tmpo)
	{
		v.t = intersect(tmpo, rt.ray);
		if ((v.t < v.near && v.t > 0) || (v.t > v.near && v.near < 0))
		{
			close = tmpo;
			v.near = v.t;
		}
		tmpo = tmpo->next;
	}
	if (v.near > 0 && close)
	{
		setnormal(close, &rt.ray, v.near);
		col = color(&rt, close, rt.lights);
	}
	if (SDL_SetRenderDrawColor(rt.rend, col.x, col.y, col.z, 255) != 0)
			sdl_error("Get color failed");
	if (SDL_RenderDrawPoint(rt.rend, v.y, v.x) != 0)
			sdl_error("draw point failed");
	rt.screen[v.y * MAXWIDTH + v.x] = col;
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
		}
	}
	rt.filter_type = 0;
	filtres(&rt);
}
