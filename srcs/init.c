/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:16:40 by yataji            #+#    #+#             */
/*   Updated: 2021/03/09 01:03:17 by yataji           ###   ########.fr       */
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
