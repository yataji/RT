/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:23:00 by yataji            #+#    #+#             */
/*   Updated: 2021/03/10 16:16:05 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	ft_strdel(value);
	return (1);
}

int			cylinder(t_obj *obj, char *str, int fd)
{
	int		l;

	l = 0;
	while (l < 4)
	{
		if (get_next_line(fd, &str) < 0)
			return (-1);
		l++;
		if (checkval(str, "\tcenter: ", 9) > 0 || checkval(str, "\tcenter:\t", 9) > 0)
			stockcylinder(obj, str);
		else if (checkval(str, "\tcolor: ", 8) > 0 || checkval(str, "\tcolor:\t", 8) > 0)
			stockcylinder(obj, str);
		else if (checkval(str, "\tradius: ", 9) > 0 || checkval(str, "\tradius:\t", 9) > 0)
			stockcylinder(obj, str);
		else if (checkval(str, "\taxis: ", 7) > 0 || checkval(str, "\taxis:\t", 7) > 0)
			stockcylinder(obj, str);
		else
			return (-1);
		obj->type = CYLINDER;
		obj->angle = 0;
		ft_strdel(&str);
	}
	return (1);
}
