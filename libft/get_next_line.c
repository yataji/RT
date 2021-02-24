/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 21:55:43 by yataji            #+#    #+#             */
/*   Updated: 2019/11/28 10:56:43 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_strsub(str, 0, i);
	return (line);
}

char	*get_rest(char *str)
{
	char	*rest;

	if (!ft_strchr(str, '\n'))
		return (NULL);
	rest = ft_strdup(ft_strchr(str, '\n') + 1);
	return (rest);
}

int		get_next_line(const int fd, char **line)
{
	static char *str[MAX_FD];
	char		buff[BUFF_SIZE + 1];
	char		*tmp;
	int			red;

	if (BUFF_SIZE < 1 || fd < 0 || fd > MAX_FD || !line)
		return (-1);
	if (!str[fd])
		str[fd] = ft_strnew(0);
	while (!ft_strchr(str[fd], '\n') && (red = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[red] = '\0';
		tmp = str[fd];
		str[fd] = ft_strjoin(str[fd], buff);
		free(tmp);
	}
	*line = get_line(str[fd]);
	tmp = str[fd];
	str[fd] = get_rest(tmp);
	free(tmp);
	if (red < 1 && !str[fd])
		return (red);
	return (1);
}
