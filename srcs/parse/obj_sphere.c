/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:49:00 by jiqarbac          #+#    #+#             */
/*   Updated: 2021/03/30 15:09:33 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	ft_sphere(t_rtv1 *rt, char *str)
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

	value = ft_strsplit(str, ':');
	if (ft_lendd(value) != 4 && ft_lendd(value) != 2)
		return (-1);
	if (ft_strcmp(value[0], " center") == 0)
		obj->center = stk(value);
	else if (ft_strcmp(value[0], " color") == 0)
		obj->color = stk(value);
	else if (ft_lendd(value) == 2 && ft_strcmp(value[0], " radius") == 0)
		obj->radius = ft_atoi(value[1]);
	else if (ft_strcmp(value[0], " trs") == 0)
		obj->trs = stk(value);
	ft_strdel(value);
	return (1);
}

// int	sphere(t_obj *obj, char *str, int fd)
// {
// 	int		l;
// 	int		check;

// 	l = 0;
// 	while (l < 4)
// 	{
// 		check = -1;
// 		if (get_next_line(fd, &str) < 0)
// 			return (-1);
// 		if (str && ck(str, " center: ", 9) > 0)
// 			check = stocksphere(obj, str);
// 		else if (str && ck(str, " color: ", 8) > 0)
// 			check = stocksphere(obj, str);
// 		else if (str && ck(str, " radius: ", 9) > 0)
// 			check = stocksphere(obj, str);
// 		else if (str && ck(str, " trs: ", 6) > 0)
// 			check = stocksphere(obj, str);
// 		else
// 			return (-1);
// 		obj->type = SPHERE;
// 		ft_strdel(&str);
// 		l++;
// 	}
// 	obj->center = plus(obj->center, obj->trs);
// 	return (1);
// }

int	sphere(t_obj *obj, char *str, int fd)
{
	int		l;
	int		check;

	l = 0;
	while (l < 4)
	{
		check = -1;
		if (get_next_line(fd, &str) < 0)
			return (-1);
		if (ck(str, " center: ", 9) > 0)
			check = stocksphere(obj, str);
		else if (ck(str, " color: ", 8) > 0)
			check = stocksphere(obj, str);
		else if (ck(str, " radius: ", 9) > 0)
			check = stocksphere(obj, str);
		else if (ck(str, " trs: ", 6) > 0)
			check = stocksphere(obj, str);
		else
			return (-1);
		obj->type = SPHERE;
		ft_strdel(&str);
		l++;
	}
	obj->center = plus(obj->center, obj->trs);
	return (1);
}
