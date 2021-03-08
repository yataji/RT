/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:18:10 by yataji            #+#    #+#             */
/*   Updated: 2021/03/08 19:39:58 by yataji           ###   ########.fr       */
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
			rt.ray = initray(x, y);
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
				// printf("%d\t", tmp->type);
				tmp = tmp->next;
			}
				// else if (tmp->type == CYLINDER)
				// norm = normcyld(&rt.ray, tmp, t);
				// else if (tmp->type == CONE)
				// norm = normcone(&rt.ray, tmp, t);
				if (t > 0 && close)
				{
					if (close->type == SPHERE)
						norm = normsphr(&rt.ray, close, t);
					lightdir = normalize(moins((t_vect){350, 350, 0}, rt.ray.hit));
					//lightdir = normalize(moins(rt.ray.hit, (t_vect){350, 350, 50}));
					double dot1 = dot(norm, lightdir);
					dot1<0 || dot1> 1 ? dot1 = 0 : 0;
					int color = 0;
					unsigned char *ptr = (unsigned char *)&color;
					ptr[0] = close->color.x; //255 * dot1;
					ptr[1] = close->color.y; //2 * dot1;
					ptr[2] = close->color.z; //2 * dot1;
					ptr[4] = 0;
					rt.mlx.dtadd[x + y * MAXWIDTH] = color;
				}
				else
					rt.mlx.dtadd[x + y * MAXWIDTH] = 0;
		}
	}
	// printf("i = %d\n", i);
	// exit(0);
	mlx_put_image_to_window(rt.mlx.ptr, rt.mlx.win_ptr, rt.mlx.img_ptr, 0, 0);
}