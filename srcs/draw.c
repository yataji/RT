/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:18:10 by yataji            #+#    #+#             */
/*   Updated: 2021/04/22 23:15:35 by yataji           ###   ########.fr       */
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

// t_ray	initrayrfr(t_rt *rt,t_ray ray, t_obj *closeobj)
// {
// 	t_ray ret;
// 	t_vect refrect;
// 	double dot1;

// 	ret.org = ray.hit;
// 	dot1 = dot(closeobj->normal, ray.dir);
// 	refrect = 

// }

// t_color		refraction(t_rt *rt, t_obj *close, t_lights *l, t_ray rayor)
// {
// 	t_ray ray;
// 	t_obj *closenew;
// 	t_var v;
// 	double t;

// 	rt->tmpo = rt->obj;
// 	if (!close || !close->refl || rt->maxref > 100)
// 		return ((t_color){0, 0, 0});
// 	ray = initrayrfr(rt, rayor, close);
// 	v.near = -1.0;
// 	closenew = NULL;
// 	while (rt->tmpo)
// 	{
// 		if (rt->tmpo != close)
// 		{
// 			t = intersect(rt->tmpo, ray);
// 			if ((t < v.near && t > 0) || (t > v.near && v.near < 0))
// 			{
// 				closenew = rt->tmpo;
// 				v.near = t;
// 			}
// 		}
// 		rt->tmpo = rt->tmpo->next;
// 	}
// }

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
		// if (close->refr)
		// 	c = add_color(refraction(rt, close, rt->tmpl, rt->ray), c);
		ret = add_color(ret, c);
		rt->tmpl = rt->tmpl->next;
	}
	return (ret);
}

void	drawcolor(t_var v, t_obj *close, t_rt rt, t_obj *tmpo)
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
int				inside_rect(t_rt *rt, SDL_Rect r)
{
	if (rt->event.i >= r.x && rt->event.i <= r.x + r.w &&
		rt->event.j >= r.y && rt->event.j <= r.y + r.h)
		return (1);
	return (0);
}

void			button_start(t_rt *rt)
{
	SDL_Rect	dest;
	SDL_Texture	*img;
	dest.x = 400;
	dest.y = 760;
	dest.w = 200;
	dest.h = 180;
	img = IMG_LoadTexture(rt->rend, "./texture/menu1.png");
	SDL_RenderCopy(rt->rend, img, NULL, &dest);
	if (inside_rect(rt, dest) == 1)
		rt->menu = 1;
}

void			button_motion(t_rt *rt)
{
	SDL_Rect	dest2;
	SDL_Texture	*img2;
	dest2.x = 100;
	dest2.y = 850;
	dest2.w = 180;
	dest2.h = 100;
	img2 = IMG_LoadTexture(rt->rend, "./texture/motion.jpg");
	SDL_RenderCopy(rt->rend, img2, NULL, &dest2);
	if (inside_rect(rt, dest2) == 1)
		rt->filter_type = 1;
}

void			button_sepia(t_rt *rt)
{
	SDL_Rect	dest3;
	SDL_Texture	*img3;
	dest3.x = 700;
	dest3.y = 850;
	dest3.w = 180;
	dest3.h = 100;
	img3 = IMG_LoadTexture(rt->rend, "./texture/sepia.jpg");
	SDL_RenderCopy(rt->rend, img3, NULL, &dest3);
	if (inside_rect(rt, dest3) == 1)
		rt->filter_type = 2;
}

void			background(t_rt *rt)
{
	SDL_Rect	dest1;
	SDL_Texture	*img1;
	dest1.x = 0;
	dest1.y = 0;
	dest1.w = MAXWIDTH;
	dest1.h = MAXHEIGHT;
	img1 = IMG_LoadTexture(rt->rend, "./texture/blow.jpg");
	SDL_RenderCopy(rt->rend, img1, NULL, &dest1);
}

void			menu(t_rt *rt)
{
	background(rt);
	button_start(rt);
	button_motion(rt);
	button_sepia(rt);
	rt->event.i = 0;
	rt->event.j = 0;
}

void	draw(t_rt	rt)
{
	t_obj		*close;
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
				close = NULL;
				v.near = -1;
				drawcolor(v, close, rt, rt.tmpo);
			}
		}
		filtres(&rt);
	}
	loop(&rt);
}

// void	*draw(void *param)
// {
// 	t_rt		*rt;
// 	t_obj		*close;
// 	t_var		v;

// 	v.y = -1;
// 	v.near = -1.0;
// 	rt = (t_rt *)param;
// 	if (rt->menu == 0)
// 		menu(rt);
// 	if (rt->menu == 1)
// 	{
// 		while (++v.y < MAXWIDTH / 2)
// 		{
// 			v.x = -1;
// 			while (++v.x < MAXHEIGHT / 2)
// 			{
// 				rt->ray = initray(rt->tmpc, v.y, v.x);
// 				rt->tmpo = rt->obj;
// 				close = NULL;
// 				v.near = -1;
// 				drawcolor(v, close, *rt, rt->tmpo);
// 			}
// 		}
// 	}
// 	rt->filter_type = 0;
// 	filtres(rt);
// 	loop(rt);
// 	return (0);
// }

// void	*draw2(void *param)
// {
// 	t_rt		*rt;
// 	t_obj		*close;
// 	t_var		v;

// 	v.y = -1;
// 	v.near = -1.0;
// 	rt = (t_rt *)param;
// 	if (rt->menu == 0)
// 		menu(rt);
// 	if (rt->menu == 1)
// 	{
// 		while (++v.y < MAXWIDTH / 2)
// 		{
// 			v.x = MAXHEIGHT / 2 - 1;
// 			while (++v.x < MAXHEIGHT)
// 			{
// 				rt->ray = initray(rt->tmpc, v.y, v.x);
// 				rt->tmpo = rt->obj;
// 				close = NULL;
// 				v.near = -1;
// 				drawcolor(v, close, *rt, rt->tmpo);
// 			}
// 		}
// 	}
// 	rt->filter_type = 0;
// 	filtres(rt);
// 	loop(rt);
// 	return (0);
// }

// void	*draw3(void *param)
// {
// 	t_rt		*rt;
// 	t_obj		*close;
// 	t_var		v;

// 	v.y = MAXWIDTH / 2 - 1;
// 	v.near = -1.0;
// 	rt = (t_rt *)param;
// 	if (rt->menu == 0)
// 		menu(rt);
// 	if (rt->menu == 1)
// 	{
// 		while (++v.y < MAXWIDTH)
// 		{
// 			v.x = -1;
// 			while (++v.x < MAXHEIGHT / 2)
// 			{
// 				rt->ray = initray(rt->tmpc, v.y, v.x);
// 				rt->tmpo = rt->obj;
// 				close = NULL;
// 				v.near = -1;
// 				drawcolor(v, close, *rt, rt->tmpo);
// 			}
// 		}
// 	}
// 	rt->filter_type = 0;
// 	filtres(rt);
// 	loop(rt);
// 	return (0);
// }

// void	*draw4(void *param)
// {
// 	t_rt		*rt;
// 	t_obj		*close;
// 	t_var		v;

// 	v.y = MAXWIDTH / 2 - 1;
// 	v.near = -1.0;
// 	rt = (t_rt *)param;
// 	if (rt->menu == 0)
// 		menu(rt);
// 	if (rt->menu == 1)
// 	{
// 		while (++v.y < MAXWIDTH)
// 		{
// 			v.x = MAXHEIGHT / 2 - 1;
// 			while (++v.x < MAXHEIGHT)
// 			{
// 				rt->ray = initray(rt->tmpc, v.y, v.x);
// 				rt->tmpo = rt->obj;
// 				close = NULL;
// 				v.near = -1;
// 				drawcolor(v, close, *rt, rt->tmpo);
// 			}
// 		}
// 	}
// 	rt->filter_type = 0;
// 	filtres(rt);
// 	loop(rt);
// 	return (0);
// }

// void			multi_thread(t_rt *rt)
// {
// 	pthread_t	thread[4];

// 	pthread_create(&thread[0], NULL, &draw, rt);
// 	pthread_create(&thread[1], NULL, &draw2, rt);
// 	pthread_create(&thread[2], NULL, &draw3, rt);
// 	pthread_create(&thread[3], NULL, &draw4, rt);
// 	pthread_join(thread[0], NULL);
// 	pthread_join(thread[1], NULL);
// 	pthread_join(thread[2], NULL);
// 	pthread_join(thread[3], NULL);
// 	// mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
// }