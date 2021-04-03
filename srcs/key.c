/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:10:21 by yataji            #+#    #+#             */
/*   Updated: 2021/03/15 11:21:07 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			keypress(int key, void *param)
{
	t_rtv1	*rt;

	rt = (t_rtv1 *)param;
	if (key == 8 && !rt->tmpc->next)
	{
		rt->ck = 0;
		rt->tmpc = rt->cam;
	}
	if (key == 8 && rt->tmpc)
	{
		if (rt->tmpc->next && rt->ck != 0)
			rt->tmpc = rt->tmpc->next;
		rt->ck++;
		mlx_clear_window(rt->mlx.img_ptr, rt->mlx.win_ptr);
		draw(*rt);
		mlx_put_image_to_window(rt->mlx.ptr, rt->mlx.win_ptr,
						rt->mlx.img_ptr, 0, 0);
	}
	key == 53 ? ft_exit(rt) : 0;
	return (0);
}
