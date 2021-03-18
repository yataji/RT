/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:01:53 by yataji            #+#    #+#             */
/*   Updated: 2021/03/18 18:52:36 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				parse1(t_rtv1 *rt, char *str)
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
		if (ft_plan(rt, str) == -1)
			return (-1);
	return (1);
}

int				parse(t_rtv1 *rt)
{
	char		*str;

	rt->check[0] = 0;
	rt->check[1] = 0;
	rt->lights = initlights();
	while (rt->fd > 2 && get_next_line(rt->fd, &str) > 0)
	{
		if (ft_strcmp(str, "camera:") == 0 && rt->check[0] == 0)
		{
			if (camera(&rt->cam, str, rt->fd) == -1)
				return (-1);
			rt->check[0]++;
		}
		else if (ft_strcmp(str, "lights:") == 0)
		{
			if (ft_lights(rt, str) == -1)
				return (-1);
		}
		else
			parse1(rt, str);
		free(str);
	}
	return (1);
}
