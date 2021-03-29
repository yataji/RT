/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:49:00 by jiqarbac          #+#    #+#             */
/*   Updated: 2021/03/29 14:49:03 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_sphere(t_rtv1 *rt, char *str)
{
	rt->tmpo = initobj();
	if (sphere(rt->tmpo, str, rt->fd) == -1)
		return (-1);
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
	if (ft_strcmp(value[0], " center") == 0)
		obj->center = stk(value);
	else if (ft_strcmp(value[0], " color") == 0)
		obj->color = stk(value);
	else if (ft_strlend(value) == 2 && ft_strcmp(value[0], " radius") == 0)
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
		if (ck(str, " center: ", 9) > 0 || ck(str, " center: ", 9) > 0)
			stocksphere(obj, str);
		else if (ck(str, " color: ", 8) > 0 || ck(str, " color: ", 8) > 0)
			stocksphere(obj, str);
		else if (ck(str, " radius: ", 9) > 0 || ck(str, " radius: ", 9) > 0)
			stocksphere(obj, str);
		else
			return (-1);
		obj->type = SPHERE;
		ft_strdel(&str);
		l++;
	}
	return (1);
}
