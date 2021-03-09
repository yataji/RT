/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:20:09 by yataji            #+#    #+#             */
/*   Updated: 2021/03/09 14:52:11 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int camera(t_cam *cam, char *str, int fd)
{
	char **value;
	int l;

	l = 0;
	while (l < 2)
	{
		if (get_next_line(fd, &str) < 0)
			return (-1);
		l++;
		if (checkval(str, "\tlokat: ", 8) > 0 || checkval(str, "\tlokat:\t", 8) > 0)
		{
			value = ft_strsplit(str, ':');
			if (ft_strlend(value) != 4)
				return (-1);
			stockcamera(cam, value, str);
			// cam->lokat.x = ft_atoi(value[1]);
			// cam->lokat.y = ft_atoi(value[2]);
			// cam->lokat.z = ft_atoi(value[3]);
		}
		else if (checkval(str, "\tlokfrm: ", 9) > 0 || checkval(str, "\tlokfrm:\t", 9) > 0)
		{
			value = ft_strsplit(str, ':');
			if (ft_strlend(value) != 4)
				return (-1);
			stockcamera(cam, value, str);
			// cam->lokfrm.x = ft_atoi(value[1]);
			// cam->lokfrm.y = ft_atoi(value[2]);
			// cam->lokfrm.z = ft_atoi(value[3]);
		}
		else
			return (-1);
		free(str);
	}
	initcamera(cam);
	return (1);
}
