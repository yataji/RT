/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:49:00 by jiqarbac          #+#    #+#             */
/*   Updated: 2021/04/17 16:26:55 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_sphere(t_rt *rt, char *str)
{
	rt->tmpo = initobj();
	if (sphere(rt->tmpo, str, rt->fd) == -1)
		return (-1);
	rt->tmpo->next = rt->obj;
	rt->obj = rt->tmpo;
	return (0);
}

int	stocksphere(t_obj *obj, char *str)
{
	char	**value;
	int		ck;

	value = ft_strsplit(str, ':');
	ck = ft_lendd(value);
	if (ck != 4 && ck != 2)
		return (-1);
	if (ck == 4 && ft_strcmp(value[0], " center") == 0)
		obj->center = stk(value);
	else if (ck == 4 && ft_strcmp(value[0], " color") == 0)
		obj->color = checkcolorvalue(value);
	else if (ck == 2 && ft_strcmp(value[0], " radius") == 0)
		obj->radius = ft_atoi(value[1]);
	else if (ck == 2 && ft_strcmp(value[0], " ref") == 0)
		obj->ref = ft_atoi(value[1]);
	else if (ck == 4 && ft_strcmp(value[0], " trs") == 0)
		obj->trs = stk(value);
	else
	{
		ft_strdel(value);
		return (-1);
	}
	return (1);
}

int	sphere(t_obj *obj, char *str, int fd)
{
	int		l;
	int		check;

	l = -1;
	while (++l < 5)
	{
		check = -1;
		if (get_next_line(fd, &str) < 0)
			return (-1);
		if (str && ck(str, " center: ", 9) > 0)
			check = stocksphere(obj, str);
		else if (str && ck(str, " color: ", 8) > 0)
			check = stocksphere(obj, str);
		else if (str && ck(str, " ref: ", 6) > 0)
			check = stocksphere(obj, str);
		else if (str && ck(str, " radius: ", 9) > 0)
			check = stocksphere(obj, str);
		else if (str && ck(str, " trs: ", 6) > 0)
			check = stocksphere(obj, str);
		if (check == -1)
			return (-1);
		obj->type = SPHERE;
		ft_strdel(&str);
	}
	obj->center = plus(obj->center, obj->trs);
	return (1);
}
