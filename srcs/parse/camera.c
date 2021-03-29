/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:20:09 by yataji            #+#    #+#             */
/*   Updated: 2021/03/29 14:49:37 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			stockcamera(t_cam *cam, char *str)
{
	char	**value;

	value = ft_strsplit(str, ':');
	if (ft_strlend(value) != 4 && ft_strlend(value) != 2)
		return (-1);
	if (ft_strcmp(value[0], " lokat") == 0)
		cam->lokat = stk(value);
	else if (ft_strcmp(value[0], " lokfrm") == 0)
		cam->lokfrm = stk(value);
	else if (ft_strlend(value) == 2 && ft_strcmp(value[0], " fov") == 0)
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
		if (ck(str, " lokat: ", 8) > 0 || ck(str, " lokat: ", 8) > 0)
			stockcamera(cam, str);
		else if (ck(str, " lokfrm: ", 9) > 0 || ck(str, " lokfrm: ", 9) > 0)
			stockcamera(cam, str);
		else if (ck(str, " fov: ", 6) > 0 || ck(str, " fov: ", 6) > 0)
			stockcamera(cam, str);
		else
			return (-1);
		ft_strdel(&str);
	}
	initcamera(cam);
	return (1);
}
