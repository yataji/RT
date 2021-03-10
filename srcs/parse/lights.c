/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:20:08 by yataji            #+#    #+#             */
/*   Updated: 2021/03/10 19:26:43 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			stocklights(t_lights *lights, char *str)
{
	char	**value;

	value = ft_strsplit(str, ':');
	if (ft_strlend(value) != 4 && ft_strlend(value) != 2)
		return (-1);
	if (ft_strlend(value) == 2 && ft_strcmp(value[0], "\tintensity") == 0)
		lights->intensity = ft_atoi(value[1]);
	else if (ft_strcmp(value[0], "\tcolor") == 0)
		lights->color = stk(value);
	else if (ft_strcmp(value[0], "\tpos") == 0)
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
		if (checkval(str, "\tintensity: ", 12) > 0 ||
			checkval(str, "\tintensity:\t", 12) > 0)
			stocklights(lights, str);
		else if (checkval(str, "\tcolor: ", 8) > 0 ||
			checkval(str, "\tcolor:\t", 8) > 0)
			stocklights(lights, str);
		else if (checkval(str, "\tpos: ", 6) > 0 ||
			checkval(str, "\tpos:\t", 6) > 0)
			stocklights(lights, str);
		else
			return (-1);
		ft_strdel(&str);
	}
	return (1);
}
