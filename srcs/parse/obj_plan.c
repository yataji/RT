/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:22:27 by yataji            #+#    #+#             */
/*   Updated: 2021/03/08 16:24:31 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int plan(t_obj *obj, char *str, int fd)
{
	char **value;
	int l;

	l = 0;
	while (l < 4)
	{
		if (get_next_line(fd, &str) < 0)
			return (-1);
		l++;
		if (checkval(str, "\tcenter: ", 9) > 0 || checkval(str, "\tcenter:\t", 9) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			obj->center.x = ft_atoi(value[1]);
			obj->center.y = ft_atoi(value[2]);
			obj->center.z = ft_atoi(value[3]);
		}
		else if (checkval(str, "\tcolor: ", 8) > 0 || checkval(str, "\tcolor:\t", 8) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			obj->color.x = ft_atoi(value[1]);
			obj->color.y = ft_atoi(value[2]);
			obj->color.z = ft_atoi(value[3]);
		}
		else if (checkval(str, "\tradius: ", 9) > 0 || checkval(str, "\tradius:\t", 9) > 0)
		{
			value = ft_strsplit(str, ':');

			free(str);
			if (ft_strlend(value) != 2)
				return (-1);
			obj->radius = ft_atoi(value[1]);
		}
		else if (checkval(str, "\taxis: ", 7) > 0 || checkval(str, "\taxis:\t", 7) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			obj->v.x = ft_atoi(value[1]);
			obj->v.y = ft_atoi(value[2]);
			obj->v.z = ft_atoi(value[3]);
		}
		else
			return (-1);
		obj->type = PLAN;
		obj->angle = 0;
	}
	return (1);
}
