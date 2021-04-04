/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:22:27 by jiqarbac          #+#    #+#             */
/*   Updated: 2021/04/04 16:00:30 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_plane(t_rtv1 *rt, char *str)
{
	rt->tmpo = initobj();
	if (plane(rt->tmpo, str, rt->fd) == -1)
		return (-1);
	rt->tmpo->next = rt->obj;
	rt->obj = rt->tmpo;
	return (0);
}

int			stockplane(t_obj *obj, char *str)
{
	char	**value;

	value = ft_strsplit(str, ':');
	if (ft_strlend(value) != 4)
		return (-1);
	else if (ft_strcmp(value[0], " center") == 0)
		obj->center = stk(value);
	else if (ft_strcmp(value[0], " color") == 0)
		obj->color = stk(value);
	else if (ft_strcmp(value[0], " axis") == 0)
		obj->v = stk(value);
	else if (ft_strcmp(value[0], " rot") == 0)
		obj->rot = stk(value);
	else if (ft_strcmp(value[0], " trs") == 0)
		obj->trs = stk(value);
	ft_strdel(value);
	return (1);
}

int			plane(t_obj *obj, char *str, int fd)
{
	int		l;
	int		check;

	l = -1;
	while (++l < 5)
	{
		check = -1;
		if (get_next_line(fd, &str) < 0)
			return (-1);
		if (ck(str, " center: ", 9) > 0)
			check = stockplane(obj, str);
		else if (ck(str, " color: ", 8) > 0)
			check = stockplane(obj, str);
		else if (ck(str, " axis: ", 7) > 0)
			check = stockplane(obj, str);
		else if (ck(str, " rot: ", 6) > 0 || ck(str, " trs: ", 6) > 0)
			check = stockplane(obj, str);
		else
			return (-1);
		obj->type = PLAN;
		ft_strdel(&str);
	}
	obj->center = plus(obj->center, obj->trs);
	return (1);
}