/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 01:02:43 by yataji            #+#    #+#             */
/*   Updated: 2021/03/10 18:09:34 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray	initray(t_rtv1 rt, int x, int y)
{
	t_ray	ray;
	double	py;
	double	px;

	px = ((2 * ((double)x + 0.5) / MAXHEIGHT) - 1) * rt.cam.plnw;
	py = (1 - (2 * ((double)y + 0.5) / MAXWIDTH)) * rt.cam.plnh;
	ray.org = rt.cam.lokfrm;
	ray.dir = plus(multi(rt.cam.u, px), multi(rt.cam.v, py));
	ray.dir = normalize(plus(ray.dir, rt.cam.w));
	return (ray);
}

void	initcamera(t_cam *cam)
{
	cam->v = (t_vect){0, 1, 0};
	cam->fov = 60 * M_PI / 180;
	cam->plnh = tan(cam->fov / 2);
	cam->plnw = cam->plnh * MAXWIDTH / MAXHEIGHT;
	cam->w = normalize(moins(cam->lokat, cam->lokfrm));
	cam->u = crosspro(cam->v, cam->w);
	cam->v = crosspro(cam->w, cam->u);
}
