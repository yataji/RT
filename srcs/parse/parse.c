/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:01:53 by yataji            #+#    #+#             */
/*   Updated: 2021/03/09 02:05:35 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int parse(t_rtv1 *rt, int fd)
{
	char *str;
	t_lights *tmpl;
	t_obj *tmpo;
	int i = 0;
	int j = 0;
	while (fd > 2 && get_next_line(fd, &str) > 0)
	{
		if (ft_strcmp(str, "camera:") == 0 && j == 0)
		{
			if (camera(&rt->cam, str, fd) == -1)
				return (-1);
			j++;
		}
		else if (ft_strcmp(str, "lights:") == 0)
		{
			tmpl = (t_lights *)malloc(sizeof(t_lights));
			if (i > i + 1)
			{
				if (lights(tmpl, str, fd) == -1)
					return (-1);
			}
			else if (lights(tmpl, str, fd) == -1)
				return (-1);
			i++;
			tmpl->next = rt->lights;
			rt->lights = tmpl;
		}
		else if (ft_strcmp(str, "sphere:") == 0)
		{
			tmpo = (t_obj *)malloc(sizeof(t_obj));
			if (i > i + 1)
			{
				if (sphere(tmpo, str, fd) == -1)
					return (-1);
			}
			if (sphere(tmpo, str, fd) == -1)
				return (-1);
			i++;
			tmpo->next = rt->obj;
			rt->obj = tmpo;
		}
		else if (ft_strcmp(str, "cylinder:") == 0)
		{
			tmpo = (t_obj *)malloc(sizeof(t_obj));
			if (i > i + 1)
			{
				if (cylinder(tmpo, str, fd) == -1)
					return (-1);
			}
			if (cylinder(tmpo, str, fd) == -1)
				return (-1);
			i++;
			tmpo->next = rt->obj;
			rt->obj = tmpo;
		}
		else if (ft_strcmp(str, "cone:") == 0)
		{
			tmpo = (t_obj *)malloc(sizeof(t_obj));
			if (i > i + 1)
			{
				if (cone(tmpo, str, fd) == -1)
					return (-1);
			}
			if (cone(tmpo, str, fd) == -1)
				return (-1);
			i++;
			tmpo->next = rt->obj;
			rt->obj = tmpo;
		}
		else if (ft_strcmp(str, "plan:") == 0)
		{
			tmpo = (t_obj *)malloc(sizeof(t_obj));
			if (i > i + 1)
			{
				if (plan(tmpo, str, fd) == -1)
					return (-1);
			}
			if (plan(tmpo, str, fd) == -1)
				return (-1);
			i++;
			tmpo->next = rt->obj;
			rt->obj = tmpo;
		}
		free(str);
	}
	return (1);
}
