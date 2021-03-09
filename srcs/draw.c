/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:18:10 by yataji            #+#    #+#             */
/*   Updated: 2021/03/09 02:38:36 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void draw(t_rtv1 rt)
{
	int x;
	int y;
	double t;
	t_obj *tmp;
	t_obj *close;
	t_vect lightdir;
	double near;

	x = -1;
	near = -1.0;
	while (++x < MAXWIDTH)
	{
		y = -1;
		while (++y < MAXHEIGHT)
		{
			rt.ray = initray(rt, x, y);
			tmp = rt.obj;
			close = NULL;
			t = -1;
			while (tmp)
			{
				if ((near = intersect(tmp, rt.ray)) > 0 && ((near < t && t > 0)  || (near > t && t < 0)))
				{
					close = tmp;
					t = near;
				}
				tmp = tmp->next;
			}
				if (t > 0 && close)
				{
					setnormal(close, &rt.ray, t);
					lightdir = normalize(moins(rt.lights->pos, rt.ray.hit));
					// lightdir = normalize(moins(rt.ray.hit, (t_vect){350, 350, 50}));
					double dot1 = dot(close->normal, lightdir);
					dot1 < 0 ? dot1 *= -1 : 0;
					int color = 0;
					unsigned char *ptr = (unsigned char *)&color;
					ptr[2] = close->color.x * dot1;
					ptr[1] = close->color.y * dot1;
					ptr[0] = close->color.z * dot1;
					ptr[3] = 0;
					rt.mlx.dtadd[x + y * MAXWIDTH] = color;
				}
				else
					rt.mlx.dtadd[x + y * MAXWIDTH] = 0;
		}
	}
	// exit(0);
	mlx_put_image_to_window(rt.mlx.ptr, rt.mlx.win_ptr, rt.mlx.img_ptr, 0, 0);
}