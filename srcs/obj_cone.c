/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:23:37 by yataji            #+#    #+#             */
/*   Updated: 2021/04/17 15:56:46 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_cone(t_rt *rt, char *str)
{
	rt->tmpo = initobj();
	if (cone(rt->tmpo, str, rt->fd) == -1)
		return (-1);
	rt->tmpo->next = rt->obj;
	rt->obj = rt->tmpo;
	return (0);
}

int	stockcone(t_obj *obj, char *str)
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
	else if (ck == 2 && ft_strcmp(value[0], " angle") == 0)
		obj->angle = ft_atoi(value[1]);
	else if (ck == 2 && ft_strcmp(value[0], " ref") == 0)
		obj->angle = ft_atoi(value[1]);
	else if (ck == 4 && ft_strcmp(value[0], " axis") == 0)
		obj->v = stk(value);
	else if (ck == 4 && ft_strcmp(value[0], " rot") == 0)
		obj->rot = stk(value);
	else if (ck == 4 && ft_strcmp(value[0], " trs") == 0)
		obj->trs = stk(value);
	else
	{
		ft_strdel(value);
		return (-1);
	}
	return (1);
}

int	cone(t_obj *obj, char *s, int fd)
{
	int	l;
	int	check;

	l = -1;
	while (++l < 7)
	{
		check = -1;
		if (get_next_line(fd, &s) < 0)
			return (-1);
		if (s && ck(s, " center: ", 9) > 0)
			check = stockcone(obj, s);
		else if (s && (ck(s, " color: ", 8) > 0 || ck(s, " angle: ", 8) > 0))
			check = stockcone(obj, s);
		else if (s && ck(s, " axis: ", 7) > 0)
			check = stockcone(obj, s);
		else if (s && ck(s, " ref: ", 6) > 0)
			check = stockcone(obj, s);
		else if (s && (ck(s, " rot: ", 6) > 0 || ck(s, " trs: ", 6) > 0))
			check = stockcone(obj, s);
		if (check == -1)
			return (-1);
		obj->type = CONE;
		ft_strdel(&s);
	}
	obj->center = plus(obj->center, obj->trs);
	return (1);
}
