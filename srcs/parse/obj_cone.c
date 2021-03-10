/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:23:37 by yataji            #+#    #+#             */
/*   Updated: 2021/03/10 16:06:07 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		stockcone(t_obj *obj, char *str)
{
	char	**value;

	value = ft_strsplit(str, ':');
	if (ft_strlend(value) != 4 && ft_strlend(value) != 2)
		return (-1);
	if (ft_strcmp(value[0], "\tcenter") == 0)
		obj->center = stk(value);
	else if (ft_strcmp(value[0], "\tcolor") == 0)
		obj->color = stk(value);
	else if (ft_strlend(value) == 2 && ft_strcmp(value[0], "\tangle") == 0)
		obj->angle = ft_atoi(value[1]);
	else if (ft_strcmp(value[0], "\taxis") == 0)
		obj->v = stk(value);
	ft_strdel(value);
	return (1);
}

int		cone(t_obj *obj, char *str, int fd)
{
	int l;

	l = 0;
	while (l < 4)
	{
		if (get_next_line(fd, &str) < 0)
			return (-1);
		l++;
		if (checkval(str, "\tcenter: ", 9) > 0 || checkval(str, "\tcenter:\t", 9) > 0)
			stockcone(obj, str);
		else if (checkval(str, "\tcolor: ", 8) > 0 || checkval(str, "\tcolor:\t", 8) > 0)
			stockcone(obj, str);
		else if (checkval(str, "\tangle: ", 8) > 0 || checkval(str, "\tangle:\t", 8) > 0)
			stockcone(obj, str);
		else if (checkval(str, "\taxis: ", 7) > 0 || checkval(str, "\taxis:\t", 7) > 0)
			stockcone(obj, str);
		else
			return (-1);
		obj->type = CONE;
		obj->radius = 0;
		ft_strdel(&str);
	}
	return (1);
}
