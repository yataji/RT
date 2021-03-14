/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:20:09 by yataji            #+#    #+#             */
/*   Updated: 2021/03/14 18:06:41 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			stockcamera(t_cam *cam, char *str)
{
	char	**value;

	value = ft_strsplit(str, ':');
	if (ft_strlend(value) != 4 && ft_strlend(value) != 2)
		return (-1);
	if (ft_strcmp(value[0], "\tlokat") == 0)
		cam->lokat = stk(value);
	else if (ft_strcmp(value[0], "\tlokfrm") == 0)
		cam->lokfrm = stk(value);
	else if (ft_strlend(value) == 2 && ft_strcmp(value[0], "\tfov") == 0)
		cam->fov = ft_atoi(value[1]);
	ft_strdel(value);
	return (1);
}

int			camera(t_cam *cam, char *str, int fd)
{
	int		l;

	l = 0;
	while (l < 3)
	{
		if (get_next_line(fd, &str) < 0)
			return (-1);
		l++;
		if (ck(str, "\tlokat: ", 8) > 0 || ck(str, "\tlokat:\t", 8) > 0)
			stockcamera(cam, str);
		else if (ck(str, "\tlokfrm: ", 9) > 0 || ck(str, "\tlokfrm:\t", 9) > 0)
			stockcamera(cam, str);
		else if (ck(str, "\tfov: ", 6) > 0 || ck(str, "\tfov:\t", 6) > 0)
			stockcamera(cam, str);
		else
			return (-1);
		ft_strdel(&str);
	}
	initcamera(cam);
	return (1);
}
