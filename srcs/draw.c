/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:18:10 by yataji            #+#    #+#             */
/*   Updated: 2021/03/12 23:11:54 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int					color(t_rtv1 *rt, t_obj *close, t_lights *lights)
{
	double			dot1;
	int				color;
	unsigned char	*ptr;
	t_vect			lightdir;

	color = 0;
	ptr = (unsigned char *)&color;
	lightdir = normalize(moins(lights->pos, rt->ray.hit));
	dot1 = dot(close->normal, lightdir);
	if (dot1 > 0)
	{
		ptr[2] = close->color.x * dot1 * lights->intensity / 100.0;
		ptr[1] = close->color.y * dot1 * lights->intensity / 100.0;
		ptr[0] = close->color.z * dot1 * lights->intensity / 100.0;
		ptr[3] = 0;
	}
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
