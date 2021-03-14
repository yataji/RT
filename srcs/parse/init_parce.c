/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:35:11 by yataji            #+#    #+#             */
/*   Updated: 2021/03/14 19:19:39 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj			*initobj(void)
{
	t_obj		*new;

	if (!(new = (t_obj *)malloc(sizeof(t_obj))))
		return (NULL);
	new->type = 0;
	new->angle = 0;
	new->radius = 0;
	new->v = (t_vect){0, 0, 0};
	new->normal = (t_vect){0, 0, 0};
	new->color = (t_color){0, 0, 0};
	new->center = (t_point){0, 0, 0};
	new->rot = (t_rot){0, 0, 0};
	new->angle = 0;
	return (new);
}

t_lights		*initlights(void)
{
	t_lights	*new;

	if (!(new = (t_lights *)malloc(sizeof(t_lights))))
		return (NULL);
	new->intensity = 0;
	new->color = (t_color){0, 0, 0};
	new->pos = (t_point){0, 0, 0};
	return (new);
}
