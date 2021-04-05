/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:25:19 by jiqarbac          #+#    #+#             */
/*   Updated: 2021/04/05 18:51:31 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

size_t		ft_strlend(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int			ck(char *s, char *check, int l)
{
	int		i;

	if (s[0] != ' ')
		return (-1);
	if (ft_strncmp(s, check, l) != 0)
		return (-1);
	i = l - 2;
	if ((s[l] < '0' || s[l] > '9') && s[l] != '-' && s[l] != '+')
		return (-1);
	while (s[++i])
	{
		if ((s[i] == ':' && s[i + 1] == ':') ||
			(s[i] == ':' && s[i + 1] == '\0') ||
			(s[i] == ':' && s[i + 1] == ' ') ||
			(s[i] == ' ' && s[i + 1] == '\0'))
			return (-1);
		else if (s[i] == ':' || s[i] == '-' || s[i] == '+' || s[i] == ' ')
		{
			if (s[i] == ':' && s[i + 1] == ':')
				return (-1);
		}
		else if (ft_isdigit(s[i]) == 0)
			return (-1);
	}
	return (1);
}
