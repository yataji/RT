/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:23:00 by yataji            #+#    #+#             */
/*   Updated: 2021/03/17 16:08:55 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_cylinder(t_rtv1 *rt, char *str)
{
	rt->tmpo = initobj();
	if (cylinder(rt->tmpo, str, rt->fd) == -1)
		return (-1);
	rt->tmpo->next = rt->obj;
	rt->obj = rt->tmpo;
	return (0);
}

int			stockcylinder(t_obj *obj, char *str)
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
	else if (ft_strcmp(value[0], "\trot") == 0)
		obj->rot = stk(value);
	ft_strdel(value);
	return (1);
}

int			cylinder(t_obj *obj, char *str, int fd)
{
	int		l;

	l = -1;
	while (++l < 5)
	{
		if (get_next_line(fd, &str) < 0)
			return (-1);
		if (ck(str, "\tcenter: ", 9) > 0 || ck(str, "\tcenter:\t", 9) > 0)
			stockcylinder(obj, str);
		else if (ck(str, "\tcolor: ", 8) > 0 || ck(str, "\tcolor:\t", 8) > 0)
			stockcylinder(obj, str);
		else if (ck(str, "\tradius: ", 9) > 0 || ck(str, "\tradius:\t", 9) > 0)
			stockcylinder(obj, str);
		else if (ck(str, "\taxis: ", 7) > 0 || ck(str, "\taxis:\t", 7) > 0)
			stockcylinder(obj, str);
		else if (ck(str, "\trot: ", 6) > 0 || ck(str, "\trot:\t", 6) > 0)
			stockcylinder(obj, str);
		else
			return (-1);
		obj->type = CYLINDER;
		ft_strdel(&str);
	}
	return (1);
}
