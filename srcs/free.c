/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:14:37 by yataji            #+#    #+#             */
/*   Updated: 2021/03/01 18:15:10 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int ft_exit(t_mlx *mlx)
{
	mlx_clear_window(mlx->ptr, mlx->win_ptr);
	mlx_destroy_window(mlx->ptr, mlx->win_ptr);
	exit(0);
	return (0);
}