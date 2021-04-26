/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 01:02:43 by yataji            #+#    #+#             */
/*   Updated: 2021/04/07 18:19:48 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray	initray(t_cam *cam, int x, int y)
{
	t_ray	ray;
	double	py;
	double	px;

	px = ((2 * ((double)x + 0.5) / MAXWIDTH) - 1) * cam->plnw;
	py = (1 - (2 * ((double)y + 0.5) / MAXHEIGHT)) * cam->plnh;
	ray.org = cam->lokfrm;
	ray.dir = plus(multi(cam->u, px), multi(cam->v, py));
	ray.dir = normalize(plus(ray.dir, cam->w));
	return (ray);
}

void	initcamera(t_cam *cam)
{
	double	dot1;

	cam->w = normalize(moins(cam->lokat, cam->lokfrm));
	dot1 = dot(cam->v, cam->w);
	if (fabs(dot1) == 1)
		cam->v = (t_vect){0, 0, -1 * dot1};
	cam->fov = cam->fov * M_PI / 180.0;
	cam->plnh = tan(cam->fov / 2.0);
	cam->plnw = cam->plnh * (double)MAXWIDTH / MAXHEIGHT;
	cam->u = crosspro(cam->v, cam->w);
	cam->v = crosspro(cam->w, cam->u);
}
