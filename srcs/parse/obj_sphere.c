/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:20:04 by yataji            #+#    #+#             */
/*   Updated: 2021/03/15 18:35:52 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_sphere(t_rtv1 *rt, char *str, int c)
{
	rt->tmpo = initobj();
	if (c != 0)
		return (-1);
	if (rt->check[0] > rt->check[0] + 1)
	{
		if (sphere(rt->tmpo, str, rt->fd) == -1)
			return (-1);
	}
	if (sphere(rt->tmpo, str, rt->fd) == -1)
		return (-1);
	rt->check[0]++;
	rt->tmpo->next = rt->obj;
	rt->obj = rt->tmpo;
	return (0);
}

int			stocksphere(t_obj *obj, char *str)
{
	char	**value;

	value = ft_strsplit(str, ':');
	if (ft_strlend(value) != 4 && ft_strlend(value) != 2)
		return (-1);
	if (ft_strcmp(value[0], "\tcenter") == 0)
		obj->center = stk(value);
	else if (ft_strcmp(value[0], "\tcolor") == 0)
		obj->color = stk(value);
	else if (ft_strlend(value) == 2 && ft_strcmp(value[0], "\tradius") == 0)
		obj->radius = ft_atoi(value[1]);
	ft_strdel(value);
	return (1);
}

int			sphere(t_obj *obj, char *str, int fd)
{
	int		l;

	l = 0;
	while (l < 3)
	{
		if (get_next_line(fd, &str) < 0)
			return (-1);
		if (ck(str, "\tcenter: ", 9) > 0 || ck(str, "\tcenter:\t", 9) > 0)
			stocksphere(obj, str);
		else if (ck(str, "\tcolor: ", 8) > 0 || ck(str, "\tcolor:\t", 8) > 0)
			stocksphere(obj, str);
		else if (ck(str, "\tradius: ", 9) > 0 || ck(str, "\tradius:\t", 9) > 0)
			stocksphere(obj, str);
		else
			return (-1);
		obj->type = SPHERE;
		ft_strdel(&str);
		l++;
	}
	return (1);
}
