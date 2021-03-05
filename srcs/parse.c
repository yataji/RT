/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:01:53 by yataji            #+#    #+#             */
/*   Updated: 2021/03/05 19:40:05 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include <fcntl.h>
#include <stdlib.h>
// char	*ft_strlcpy(char *dst, const char *src, int size)
// {
// 	int		i;

// 	i = 0;
// 	while (src[i] && i < size)
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (dst);
// }

size_t	ft_strlend(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		checkc(char *s, char **value)
{
	int	i;
	int j;
	if (ft_strcmp(value[0], s) != 0)
	{
		printf("jj\n");
		return (-1);
	}
	i = 0;
	while(value[++i])
	{
		j = -1;
		while(value[i][++j])
		{
			if (ft_isdigit(value[i][j]) == 0)
				return (-1);
		}
	}
	return (0);
}

void		camera(t_cam *cam, char *str, int fd)
{
	char	**value;
	char	*check;
	int		i;

	if(get_next_line(fd, &str) < 0)
		return ;
	check = ft_strtrim(str);
	if (ft_strncmp(check, "lokat:", 6) == 0)
	{
			printf("jkfdsa");
			value = ft_strsplit(check, ':');
			if (ft_strlend(value) == 4)
			{
				if (checkc("lokat", value) < 0)
					return ;
				cam->lokat.x = ft_atoi(value[1]);
				cam->lokat.y = ft_atoi(value[2]);
				cam->lokat.z = ft_atoi(value[3]);
			}
	}
	free(check);
	if(get_next_line(fd, &str) < 0)
		return ;
	check = ft_strtrim(str);
	if (ft_strncmp(check, "lokfrm:", 7) == 0)
	{
			printf("jkfdsa");
			value = ft_strsplit(check, ':');
			if (ft_strlend(value) == 4)
			{
				cam->lokfrm.x = ft_atoi(value[1]);
				cam->lokfrm.y = ft_atoi(value[2]);
				cam->lokfrm.z = ft_atoi(value[3]);
			}
	}
	free(check);
}

t_rtv1	parse()
{
	char		*str;
	int			fd;
	t_rtv1		rt;
	
	fd = open("../rtv1.yaml", O_RDONLY);
	while (fd > 2 && get_next_line(fd, &str) > 0)
	{
		if (ft_strcmp(ft_strtrim(str), "camera:") == 0)
		{
			camera(&rt.cam, str, fd);
		}
		// if (ft_strcmp(str, "light:") == 0)
		// 	light();
		// if (ft_strcmp(str, "sphere:") == 0)
		// 	sphere();
		// if (ft_strcmp(str, "cylinder:") == 0)
		// 	cylinder();
		// if (ft_strcmp(str, "cone:") == 0)
		// 	cone();
		// if (ft_strcmp(str, "plan:") == 0)
		// 	plan();
	}
	return (rt);
}

int main()
{
	t_rtv1 rt = parse();
	printf("x: %lf\ty: %lf\tz: %lf\n", rt.cam.lokat.x, rt.cam.lokat.y, rt.cam.lokat.z);
	printf("x: %lf\ty: %lf\tz: %lf\n", rt.cam.lokfrm.x, rt.cam.lokfrm.y, rt.cam.lokfrm.z);
	return(0);
}