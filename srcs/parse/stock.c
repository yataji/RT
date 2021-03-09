/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:25:20 by yataji            #+#    #+#             */
/*   Updated: 2021/03/09 14:35:39 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void stocklights(t_lights *lights, char **value, char *str)
{
	if (ft_strlend(value) == 2)
		lights->intensity = ft_atoi(value[1]);
	else if (ft_strncmp(str, value[0], 6) == 0)
	{
		lights->color.x = ft_atoi(value[1]);
		lights->color.y = ft_atoi(value[2]);
		lights->color.z = ft_atoi(value[3]);
	}
	else if (ft_strncmp(str, value[0], 4) == 0)
	{
		lights->pos.x = ft_atoi(value[1]);
		lights->pos.y = ft_atoi(value[2]);
		lights->pos.z = ft_atoi(value[3]);
	}
}

void	stockcamera(t_cam *cam, char **value, char *str)
{
	if (ft_strncmp(str, value[0], 6) == 0)
	{
		cam->lokat.x = ft_atoi(value[1]);
		cam->lokat.y = ft_atoi(value[2]);
		cam->lokat.z = ft_atoi(value[3]);
	}
	else if (ft_strncmp(str, value[0], 7) == 0)
	{
		cam->lokfrm.x = ft_atoi(value[1]);
		cam->lokfrm.y = ft_atoi(value[2]);
		cam->lokfrm.z = ft_atoi(value[3]);
	}
}

// void	stockcylinder(t_obj *obj, char **value, char *str)
// {
// 	if (ft_strlend(value) == 2)
// 		obj->radius = ft_atoi(value[1]);
// 	if (ft_strncmp(str, value[0], 7) == 0)
// 	{
// 		obj->center.x = ft_atoi(value[1]);
// 		obj->center.y = ft_atoi(value[2]);
// 		obj->center.z = ft_atoi(value[3]);
// 	}
// 	else if (ft_strncmp(str, value[0], 6) == 0)
// 	{
// 		obj->color.x = ft_atoi(value[1]);
// 		obj->color.y = ft_atoi(value[2]);
// 		obj->color.z = ft_atoi(value[3]);
// 		printf("%f\t%f\t%f\nstr: |%s\nval: |%s", obj->color.x, obj->color.y, obj->color.z, str, value[0]);
// 		exit (0);
// 	}
// 	if (ft_strncmp(str, value[0], 5) == 0)
// 	{
// 		obj->v.x = ft_atoi(value[1]);
// 		obj->v.y = ft_atoi(value[2]);
// 		obj->v.z = ft_atoi(value[3]);
// 	}
// }
