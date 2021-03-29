/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:23:37 by yataji            #+#    #+#             */
/*   Updated: 2021/03/27 19:25:55 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_cone(t_rtv1 *rt, char *str)
{
	rt->tmpo = initobj();
	if (cone(rt->tmpo, str, rt->fd) == -1)
		return (-1);
	rt->tmpo->next = rt->obj;
	rt->obj = rt->tmpo;
	return (0);
}

int		stockcone(t_obj *obj, char *str)
{
	char	**value;

	value = ft_strsplit(str, ':');
	if (ft_strlend(value) != 4 && ft_strlend(value) != 2)
		return (-1);
	if (ft_strcmp(value[0], " center") == 0)
		obj->center = stk(value);
	else if (ft_strcmp(value[0], " color") == 0)
		obj->color = stk(value);
	else if (ft_strlend(value) == 2 && ft_strcmp(value[0], " angle") == 0)
		obj->angle = ft_atoi(value[1]);
	else if (ft_strcmp(value[0], " axis") == 0)
		obj->v = stk(value);
	else if (ft_strcmp(value[0], " rot") == 0)
		obj->rot = stk(value);
	ft_strdel(value);
	return (1);
}

int		cone(t_obj *obj, char *str, int fd)
{
	int	l;
	int	check;

	l = -1;
	while (++l < 5)
	{
		check = -1;
		if (get_next_line(fd, &str) < 0)
			return (-1);
		if (ck(str, " center: ", 9) > 0 || ck(str, " center: ", 9) > 0)
			check = stockcone(obj, str);
		else if (ck(str, " color: ", 8) > 0 || ck(str, " color: ", 8) > 0)
			check = stockcone(obj, str);
		else if (ck(str, " angle: ", 8) > 0 || ck(str, " angle: ", 8) > 0)
			check = stockcone(obj, str);
		else if (ck(str, " axis: ", 7) > 0 || ck(str, " axis: ", 7) > 0)
			check = stockcone(obj, str);
		else if (ck(str, " rot: ", 6) > 0 || ck(str, " rot: ", 6) > 0)
			check = stockcone(obj, str);
		if (check == -1)
			return (-1);
		obj->type = CONE;
		ft_strdel(&str);
	}
	return (1);
}
