/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 01:02:43 by yataji            #+#    #+#             */
/*   Updated: 2021/03/28 21:56:46 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray		initray(t_rtv1 rt, int x, int y)
{
	t_ray	ray;
	double	py;
	double	px;

	px = ((2 * ((double)x + 0.5) / MAXWIDTH) - 1) * rt.cam.plnw;
	py = (1 - (2 * ((double)y + 0.5) / MAXHEIGHT)) * rt.cam.plnh;
	ray.org = rt.cam.lokfrm;
	ray.dir = plus(multi(rt.cam.u, px), multi(rt.cam.v, py));
	ray.dir = normalize(plus(ray.dir, rt.cam.w));
	return (ray);
}

void		initcamera(t_cam *cam)
{
	double	dot1;

	cam->w = normalize(moins(cam->lokat, cam->lokfrm));
	dot1 = dot((t_vect){0, 1, 0}, cam->w);
	if (fabs(dot1) == 1)
		cam->v = (t_vect){0, 0, -1 * dot1};
	else
		cam->v = (t_vect){0, 1, 0};
	cam->fov = cam->fov * M_PI / 180.0;
	cam->plnh = tan(cam->fov / 2.0);
	cam->plnw = cam->plnh * (double)MAXWIDTH / MAXHEIGHT;
	cam->u = crosspro(cam->v, cam->w);
	cam->v = crosspro(cam->w, cam->u);
}
