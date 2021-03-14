/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:18:10 by yataji            #+#    #+#             */
/*   Updated: 2021/03/14 01:59:48 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_color				add_color(t_color c1, t_color c2)
{
	t_color	ret;
	double	tmp;

	tmp = c1.x + c2.x;
	ret.x = tmp > 255 ? 255 : tmp; 	
	tmp = c1.y + c2.y;
	ret.y = tmp > 255 ? 255 : tmp; 	
	tmp = c1.z + c2.z;
	ret.z = tmp > 255 ? 255 : tmp; 	
	return (ret);
}

int				shadow(t_rtv1 *rt, t_obj *close)
{
	t_obj*	tmp;
	t_var	v;
	t_ray	shadow_r;
	double	dist;
	
	tmp = rt->obj;
	shadow_r.org = rt->lights->pos;
	dist = dot(moins(rt->ray.hit, rt->lights->pos), moins(rt->ray.hit, rt->lights->pos));
	shadow_r.dir = normalize(moins(rt->ray.hit, rt->lights->pos));
	while (tmp)
	{
		if ((v.near = intersect(tmp, shadow_r)) > 0 && ((v.near < v.t && v.t > 0)
			|| (v.near > v.t && v.t < 0)))
		{
			v.t = v.near;
			if (dot(multi(shadow_r.dir, v.t), multi(shadow_r.dir, v.t)) < dist)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

t_color				multi_color(t_color c1, double scal)
{
	t_color	ret;
	double	tmp;

	tmp = c1.x * scal;
	ret.x = tmp > 255 ? 255 : tmp; 	
	tmp = c1.y * scal;
	ret.y = tmp > 255 ? 255 : tmp; 	
	tmp = c1.z * scal;
	ret.z = tmp > 255 ? 255 : tmp; 	
	return (ret);
}

int					color(t_rtv1 *rt, t_obj *close, t_lights *lights)
{
	double			dot1;
	int				color;
	unsigned char	*ptr;
	t_vect			lightdir;
	t_vect			reflect;
	t_color			c;
	t_color			ret;
	int				shad;

	color = 0;
	ptr = (unsigned char *)&color;
	ret = multi(close->color, 0.2);
	c = multi(close->color, 0);
	lightdir = normalize(moins(lights->pos, rt->ray.hit));
	dot1 = dot(close->normal, lightdir);
	// Diffuse
	if (dot1 > 0)
	{
		c = add_color(c, multi_color(close->color, dot1  * lights->intensity / 100.0));
	}
	// specular
	reflect = normalize(moins(lightdir, multi(close->normal, 2 * dot1)));
	if ((dot1 = dot(reflect, normalize(moins(rt->ray.hit, rt->ray.org)))) > 0)
		c = add_color(c, multi_color(lights->color, powf(dot1, 80)));
	//shadow
	
	ret = add_color(ret, c);	
	ptr[2] = ret.x;
	ptr[1] = ret.y;
	ptr[0] = ret.z;
	ptr[3] = 0;
	return (color);
}

void				draw2(t_var v, t_obj *close, t_rtv1 rt, t_obj *tmp)
{
	while (tmp)
	{
		if ((v.near = intersect(tmp, rt.ray)) > 0 && ((v.near < v.t && v.t > 0)
			|| (v.near > v.t && v.t < 0)))
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

void				draw(t_rtv1 rt)
{
	t_obj			*close;
	t_obj			*tmp;
	t_var			v;

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
