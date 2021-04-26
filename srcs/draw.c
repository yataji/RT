/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:18:10 by yataji            #+#    #+#             */
/*   Updated: 2021/04/26 15:23:41 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	ambtext(t_rt *rt, t_obj *close)
{
	t_color	ret;

	ret = multi(close->color, rt->cam->ambiante);
	if (ft_strcmp(close->texture, ".") != 0)
	{
		texture(close, rt->ray.hit);
		ret = close->color;
	}
	return (ret);
}

t_color	color(t_rt *rt, t_obj *close, t_lights *lights)
{
	t_color	c;
	t_color	ret;
	int		shad;

	ret = ambtext(rt, close);
	rt->tmpl = lights;
	while (rt->tmpl)
	{
		c = diffuspclr(rt->ray, close, rt->tmpl);
		if (lights->intensity > 0)
			shad = shadow(rt, rt->tmpl, close);
		if (!shad)
			c =  multi(close->color, 0.1);
		if (shad == -1)
			c = multi(close->color, 0.2);
		if (shad && close->refl)
			c = add_color(reflection(rt, close, rt->tmpl, rt->ray), c);
		if (shad && close->refr)
			c = add_color(refraction(rt, close, rt->tmpl, rt->ray), c);
		ret = add_color(ret, c);
		rt->tmpl = rt->tmpl->next;
	}
	return (ret);
}

void	drawcolor(t_var v, t_rt rt, t_obj *tmpo)
{
	t_color	col;
	t_obj	*close;

	close = NULL;
	col = (t_color){0, 0, 0};
	while (tmpo)
	{
		if (!tmpo->neg_obj)
		{
			v.t = intersect(&tmpo, rt.ray) + 0.0001;
			if ((v.t < v.near && v.t > 0) || (v.t > v.near && v.near < 0))
			{
				close = tmpo;
				v.near = v.t;
			}
		}
		tmpo = tmpo->next;
	}
	if (v.near > 0 && close)
	{
		rt.ray.hit = close->hit;
		setnormal(close, &rt.ray, v.near);
		col = color(&rt, close, rt.lights);
	}
	if (SDL_SetRenderDrawColor(rt.rend, col.x, col.y, col.z, 255) != 0)
		sdl_error("Get color failed");
	if (SDL_RenderDrawPoint(rt.rend, v.y, v.x) != 0)
		sdl_error("draw point failed");
	rt.screen[v.y * MAXWIDTH + v.x] = col;
}

int	inside_rect(t_rt *rt, SDL_Rect r)
{
	if (rt->event.i >= r.x && rt->event.i <= r.x + r.w
		&& rt->event.j >= r.y && rt->event.j <= r.y + r.h)
		return (1);
	return (0);
}

void	draw(t_rt	rt)
{
	t_var		v;

	v.y = -1;
	v.near = -1.0;
	if (rt.menu == 0)
		menu(&rt);
	if (rt.menu == 1)
	{
		while (++v.y < MAXWIDTH)
		{
			v.x = -1;
			while (++v.x < MAXHEIGHT)
			{
				rt.ray = initray(rt.tmpc, v.y, v.x);
				rt.tmpo = rt.obj;
				v.near = -1;
				drawcolor(v, rt, rt.tmpo);
			}
		}
		filtres(&rt);
	}
	loop(&rt);
}
