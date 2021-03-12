/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:01:53 by yataji            #+#    #+#             */
/*   Updated: 2021/03/12 19:22:38 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				parse(t_rtv1 *rt)
{
	char		*str;
	t_lights	*tmpl;
	t_obj		*tmpo;
	int			check[2];

	check[0] = 0;
	check[1] = 0;
	while (rt->fd > 2 && get_next_line(rt->fd, &str) > 0)
	{
		if (ft_strcmp(str, "camera:") == 0 && check[1] == 0)
		{
			if (camera(&rt->cam, str, rt->fd) == -1)
				return (-1);
			check[1]++;
		}
		else if (ft_strcmp(str, "lights:") == 0)
		{
			tmpl = (t_lights *)malloc(sizeof(t_lights));
			if (check[0] > check[0] + 1)
			{
				if (lights(tmpl, str, rt->fd) == -1)
					return (-1);
			}
			else if (lights(tmpl, str, rt->fd) == -1)
				return (-1);
			check[0]++;
			tmpl->next = rt->lights;
			rt->lights = tmpl;
		}
		else if (ft_strcmp(str, "sphere:") == 0)
		{
			tmpo = (t_obj *)malloc(sizeof(t_obj));
			if (check[0] > check[0] + 1)
			{
				if (sphere(tmpo, str, rt->fd) == -1)
					return (-1);
			}
			if (sphere(tmpo, str, rt->fd) == -1)
				return (-1);
			check[0]++;
			tmpo->next = rt->obj;
			rt->obj = tmpo;
		}
		else if (ft_strcmp(str, "cylinder:") == 0)
		{
			tmpo = (t_obj *)malloc(sizeof(t_obj));
			if (check[0] > check[0] + 1)
			{
				if (cylinder(tmpo, str, rt->fd) == -1)
					return (-1);
			}
			if (cylinder(tmpo, str, rt->fd) == -1)
				return (-1);
			check[0]++;
			tmpo->next = rt->obj;
			rt->obj = tmpo;
		}
		else if (ft_strcmp(str, "cone:") == 0)
		{
			tmpo = (t_obj *)malloc(sizeof(t_obj));
			if (check[0] > check[0] + 1)
			{
				if (cone(tmpo, str, rt->fd) == -1)
					return (-1);
			}
			if (cone(tmpo, str, rt->fd) == -1)
				return (-1);
			check[0]++;
			tmpo->next = rt->obj;
			rt->obj = tmpo;
		}
		else if (ft_strcmp(str, "plan:") == 0)
		{
			tmpo = (t_obj *)malloc(sizeof(t_obj));
			if (check[0] > check[0] + 1)
			{
				if (plan(tmpo, str, rt->fd) == -1)
					return (-1);
			}
			if (plan(tmpo, str, rt->fd) == -1)
				return (-1);
			check[0]++;
			tmpo->next = rt->obj;
			rt->obj = tmpo;
		}
		free(str);
	}
	return (1);
}
