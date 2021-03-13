/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:22:27 by yataji            #+#    #+#             */
/*   Updated: 2021/03/13 16:43:54 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_plan(t_rtv1 *rt, char *str)
{
	rt->tmpo = initobj();
	if (rt->check[0] > rt->check[0] + 1)
	{
		if (plan(rt->tmpo, str, rt->fd) == -1)
			return (-1);
	}
	if (plan(rt->tmpo, str, rt->fd) == -1)
		return (-1);
	rt->check[0]++;
	rt->tmpo->next = rt->obj;
	rt->obj = rt->tmpo;
	return (0);
}

int			stockplan(t_obj *obj, char *str)
{
	char	**value;

	value = ft_strsplit(str, ':');
	if (ft_strlend(value) != 4 && ft_strlend(value) != 2)
		return (-1);
	else if (ft_strcmp(value[0], "\tcenter") == 0)
		obj->center = stk(value);
	else if (ft_strcmp(value[0], "\tcolor") == 0)
		obj->color = stk(value);
	else if (ft_strlend(value) == 2 && ft_strcmp(value[0], "\tradius") == 0)
		obj->radius = ft_atoi(value[1]);
	else if (ft_strcmp(value[0], "\taxis") == 0)
		obj->v = stk(value);
	ft_strdel(value);
	return (1);
}

int			plan(t_obj *obj, char *str, int fd)
{
	int		l;

	l = -1;
	while (++l < 4)
	{
		if (get_next_line(fd, &str) < 0)
			return (-1);
		if (checkval(str, "\tcenter: ", 9) > 0 ||
			checkval(str, "\tcenter:\t", 9) > 0)
			stockplan(obj, str);
		else if (checkval(str, "\tcolor: ", 8) > 0 ||
			checkval(str, "\tcolor:\t", 8) > 0)
			stockplan(obj, str);
		else if (checkval(str, "\tradius: ", 9) > 0 ||
			checkval(str, "\tradius:\t", 9) > 0)
			stockplan(obj, str);
		else if (checkval(str, "\taxis: ", 7) > 0 ||
			checkval(str, "\taxis:\t", 7) > 0)
			stockplan(obj, str);
		else
			return (-1);
		obj->type = PLAN;
		ft_strdel(&str);
	}
	return (1);
}
