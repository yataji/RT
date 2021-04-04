/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:20:08 by jiqarbac          #+#    #+#             */
/*   Updated: 2021/04/04 15:48:46 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_lights(t_rtv1 *rt, char *str)
{
	rt->tmpl = initlights();
	if (lights(rt->tmpl, str, rt->fd) == -1)
		return (-1);
	rt->tmpl->next = rt->lights;
	rt->lights = rt->tmpl;
	return (0);
}

int			stocklights(t_lights *lights, char *str)
{
	char	**value;

	value = ft_strsplit(str, ':');
	if (ft_strlend(value) != 4 && ft_strlend(value) != 2)
		return (-1);
	if (ft_strlend(value) == 2 && ft_strcmp(value[0], " intensity") == 0)
	{
		lights->intensity = ft_atoi(value[1]);
		lights->intensity = lights->intensity > 100 ? 100 : lights->intensity;
	}
	else if (ft_strcmp(value[0], " color") == 0)
		lights->color = stk(value);
	else if (ft_strcmp(value[0], " pos") == 0)
		lights->pos = stk(value);
	ft_strdel(value);
	return (1);
}

int			lights(t_lights *lights, char *str, int fd)
{
	int		l;

	l = 0;
	while (l < 3)
	{
		if (get_next_line(fd, &str) < 0)
			return (-1);
		l++;
		if (ck(str, " intensity: ", 12) > 0)
			stocklights(lights, str);
		else if (ck(str, " color: ", 8) > 0)
			stocklights(lights, str);
		else if (ck(str, " pos: ", 6) > 0)
			stocklights(lights, str);
		else
			return (-1);
		ft_strdel(&str);
	}
	return (1);
}
