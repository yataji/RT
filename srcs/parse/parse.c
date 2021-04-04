/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:48:30 by jiqarbac          #+#    #+#             */
/*   Updated: 2021/04/04 15:50:07 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				parse_objs(t_rtv1 *rt, char *str)
{
	if (ft_strcmp(str, "sphere:") == 0)
	{
		if (ft_sphere(rt, str) == -1)
			return (-1);
	}
	else if (ft_strcmp(str, "cylinder:") == 0)
	{
		if (ft_cylinder(rt, str) == -1)
			return (-1);
	}
	else if (ft_strcmp(str, "cone:") == 0)
	{
		if (ft_cone(rt, str) == -1)
			return (-1);
	}
	else if (ft_strcmp(str, "plane:") == 0)
	{
		if (ft_plane(rt, str) == -1)
			return (-1);
	}
	else
		return (-1);
	return (1);
}

int				parse(t_rtv1 *rt)
{
	char		*str;

	while (rt->fd > 2 && get_next_line(rt->fd, &str) > 0)
	{
		if (ft_strcmp(str, "camera:") == 0)
		{
			if (ft_cam(rt, str) == -1)
				return (-1);
		}
		else if (ft_strcmp(str, "lights:") == 0)
		{
			if (ft_lights(rt, str) == -1)
				return (-1);
		}
		else if (parse_objs(rt, str) == -1)
		{
			free(str);
			return (-1);
		}
		free(str);
	}
	return (1);
}
