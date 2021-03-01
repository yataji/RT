/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:27:45 by yataji            #+#    #+#             */
/*   Updated: 2021/03/01 19:22:58 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double sphrintr(t_obj *sphere, t_ray ray)
{
	t_vect oc;
	t_math calc;

	oc = (t_vect){ray.org.x - sphere->center.x, ray.org.y - sphere->center.y, ray.org.z - sphere->center.z};
	calc.a = dot(ray.dir, ray.dir);
	calc.b = 2 * dot(ray.dir, oc);
	calc.c = dot(oc, oc) - multidbl(sphere->radius, sphere->radius, 1);
	calc.delta = multidbl(calc.b, calc.b, 1) - multidbl(4, calc.a, calc.c);
	return (checkt(calc));
}

t_vect	normsphr(t_ray *ray, t_obj *obj, double t)
{
	t_vect	norm;

	ray->hit = plus(ray->org, multi(ray->dir, t));
	norm = moins(ray->hit, obj->center);
	norm = normalize(norm);
	return (norm);
}

void drawsphr(t_rtv1 rt)
{
	int x;
	int y;
	double t;
	// t_vect norm;
	t_obj *tmp;
	// t_vect lightdir;

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
				// norm = 
				if (t >= 0) 
				{
					// lightdir = normalize(moins((t_vect){350, 350, 0}, rt.ray.hit));
					// double dot1 = dot(norm, lightdir);
					// dot1 < 0 || dot1 > 1 ? dot1 = 0 : 0;
					// int color = 0;
					// unsigned char *ptr = (unsigned char *)&color;
					// ptr[0] = 255 * dot1;
					// ptr[1] = 2 * dot1;
					// ptr[2] = 2 * dot1;
					rt.mlx.dtadd[x + y * MAXWIDTH] = 0xff;//color;
				}
				else
					rt.mlx.dtadd[x + y * MAXWIDTH] = 0;
				tmp = tmp->next;
			}
		}
	}
	mlx_put_image_to_window(rt.mlx.ptr, rt.mlx.win_ptr, rt.mlx.img_ptr, 0, 0);
}