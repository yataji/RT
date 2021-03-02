/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:18:10 by yataji            #+#    #+#             */
/*   Updated: 2021/03/01 17:17:19 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void draw(t_rtv1 rt)
{
	int x;
	int y;
	double t;
	t_vect norm;
	t_obj *tmp;
	t_vect lightdir;

	x = -1;
	while (++x < MAXWIDTH)
	{
		y = -1;
		while (++y < MAXHEIGHT)
		{
			rt.ray = initray(x, y);
			tmp = rt.obj;
			while (tmp)
			{
				t = intersect(tmp, rt.ray);
				// norm = normsphr(&rt.ray, tmp, t);
				// norm = normcyld(&rt.ray, tmp, t);
				norm = normcone(&rt.ray, tmp, t);
				if (t >= 0) 
				{
					// lightdir = normalize(moins((t_vect){350, 350, 0}, rt.ray.hit));
					lightdir = normalize(moins(rt.ray.hit, (t_vect){350, 350, 0}));
					double dot1 = dot(norm, lightdir);
					dot1 < 0 || dot1 > 1 ? dot1 = 0 : 0;
					int color = 0;
					unsigned char *ptr = (unsigned char *)&color;
					ptr[0] = 255 * dot1;
					ptr[1] = 2 * dot1;
					ptr[2] = 2 * dot1;
                    ptr[4] = 0;
					rt.mlx.dtadd[x + y * MAXWIDTH] = color;
				}
				else
					rt.mlx.dtadd[x + y * MAXWIDTH] = 0;
				tmp = tmp->next;
			}
		}
	}
	mlx_put_image_to_window(rt.mlx.ptr, rt.mlx.win_ptr, rt.mlx.img_ptr, 0, 0);
}