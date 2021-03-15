/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:14:37 by yataji            #+#    #+#             */
/*   Updated: 2021/03/15 17:30:17 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_free(t_obj **obj, t_lights **lights)
{
	t_lights	*tmpl;
	t_obj		*tmpo;

	while ((*obj))
	{
		tmpo = (*obj)->next;
		free((*obj));
		(*obj) = NULL;
		(*obj) = tmpo;
	}
	while ((*lights))
	{
		tmpl = (*lights)->next;
		free((*lights));
		(*lights) = NULL;
		(*lights) = tmpl;
	}
}

int		ft_exit(t_rtv1 *rt)
{
	mlx_clear_window(rt->mlx.ptr, rt->mlx.win_ptr);
	mlx_destroy_window(rt->mlx.ptr, rt->mlx.win_ptr);
	ft_free(&rt->obj, &rt->lights);
	exit(0);
	return (0);
}
