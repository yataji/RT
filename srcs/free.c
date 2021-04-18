/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:14:37 by yataji            #+#    #+#             */
/*   Updated: 2021/04/04 15:44:32 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// void	ft_free_obj(t_rt *rt)
// {
// 	while (rt->lights)
// 	{
// 		free(rt->lights);
// 		rt->lights = rt->lights->next;
// 	}
// 	free(rt->camera);
// 	ft_lstdel(&rt->obj);
// }

void	ft_free(t_obj **obj, t_lights **lights, t_cam **cam)
{
	t_obj		*tmpo;
	t_lights	*tmpl;
	t_cam		*tmpc;

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
	while ((*cam))
	{
		tmpc = (*cam)->next;
		free((*cam));
		(*cam) = NULL;
		(*cam) = tmpc;
	}
}

int	ft_exit(t_rt *rt)
{
	// mlx_clear_window(rt->mlx.ptr, rt->mlx.win_ptr);
	// mlx_destroy_window(rt->mlx.ptr, rt->mlx.win_ptr);
	// mlx_destroy_image(rt->mlx.ptr, rt->mlx.img_ptr);
	ft_free(&rt->obj, &rt->lights, &rt->cam);
	exit(0);
	return (0);
}
