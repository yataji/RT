/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:16:40 by yataji            #+#    #+#             */
/*   Updated: 2021/03/01 18:22:05 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_mlx		init()
{
	t_mlx	mlx;

	mlx.ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.ptr, MAXWIDTH, MAXHEIGHT, "rtv1");
	mlx.img_ptr = mlx_new_image(mlx.ptr, MAXWIDTH, MAXHEIGHT);
	mlx.dtadd = (int *)mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.szln, &mlx.end);
	return (mlx);
}

t_ray initray(int x, int y)
{
	t_ray ray;

	ray.org = (t_point){x, y, 0};
	ray.dir = (t_vect){0, 0, 1};
	return (ray);
}