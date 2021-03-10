/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:20:04 by yataji            #+#    #+#             */
/*   Updated: 2021/03/10 15:50:22 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	if (ft_strlend(value) == 2 && ft_strcmp(value[0], "\tradius") == 0)
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
		l++;
		if (checkval(str, "\tcenter: ", 9) > 0 || checkval(str, "\tcenter:\t", 9) > 0)
			stocksphere(obj, str);
		else if (checkval(str, "\tcolor: ", 8) > 0 || checkval(str, "\tcolor:\t", 8) > 0)
			stocksphere(obj, str);
		else if (checkval(str, "\tradius: ", 9) > 0 || checkval(str, "\tradius:\t", 9) > 0)
			stocksphere(obj, str);
		else
			return (-1);
		obj->type = SPHERE;
		obj->v = (t_vect){0, 0, 0};
		obj->angle = 0;
		ft_strdel(&str);
	}
	return (1);
}
