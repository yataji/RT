/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:01:53 by yataji            #+#    #+#             */
/*   Updated: 2021/03/27 11:52:15 by yataji           ###   ########.fr       */
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
		if (ft_plan(rt, str) == -1)
			return (-1);
	}
	else
		return (-1);
	return (1);
}

int				parse(t_rtv1 *rt)
{
	char		*str;

	rt->ck[0] = 0;
	rt->ck[1] = 0;
	while (rt->fd > 2 && get_next_line(rt->fd, &str) > 0)
	{
		if (rt->ck[0] == 0 && ft_strcmp(str, "camera:") == 0)
		{
			if (camera(&rt->cam, str, rt->fd) == -1)
				return (-1);
			rt->ck[0]++;
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
