/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:14:37 by yataji            #+#    #+#             */
/*   Updated: 2021/03/15 12:23:22 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_free(t_rtv1 **rt)
{
	t_rtv1	*tmp = NULL;

	while ((*rt)->obj)
	{
		tmp->obj = (*rt)->obj->next;
		free((*rt)->obj);
		(*rt)->obj = NULL;
		(*rt)->obj = tmp->obj;
	}
	while ((*rt)->lights)
	{
		tmp->lights = (*rt)->lights->next;
		free((*rt)->lights);
		(*rt)->lights = NULL;
		(*rt)->lights = tmp->lights;
	}
}

int		ft_exit(t_rtv1 *rt)
{
	mlx_clear_window(rt->mlx.ptr, rt->mlx.win_ptr);
	mlx_destroy_window(rt->mlx.ptr, rt->mlx.win_ptr);
	// ft_free(&rt);
	exit(0);
	return (0);
}
