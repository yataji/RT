/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:25:19 by jiqarbac          #+#    #+#             */
/*   Updated: 2021/04/22 20:32:13 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int stockobj(t_obj *obj, int id, char *s, int fd)
{
	int l;
	int i;
	int	c;
	int j;
	char **value;

	i = -1;
	j = 0;
	if (id == SPHERE)
		l = 13;
	else if (id == PLANE)
		l = 15;
	else if (id == CONE || id == CYLINDER)
		l = 16;
	else if (id == PARAPLOID)
		l = 6;
	while (++i < l)
	{
		if (get_next_line(fd, &s) < 0)
			return (-1);
		if (!s)
			return (-1);
		value = ft_strsplit(s, ':');
		c = ft_lendd(value);
		if (c != 2 && c != 4)
			return (-1);
		if (obj->type != PARAPLOID && obj->type != SPHERE && c == 2 && ck(s, " size: ", 7) && !ft_strcmp(value[0], " size"))
			obj->size = abs(ft_atoi(value[1]));
		else if (obj->type != PARAPLOID && c == 2 && !ft_strcmp(value[0], " texture"))
		{
			value[1] = ft_strtrim(value[1]);
			if (!parse_texture(obj, value[1]))
			{
				return (-1);
			}
		}
		else if (obj->type != PARAPLOID && obj->type != CUBE && c == 4 && ck(s, " slice: ", 8) > 0 && !ft_strcmp(value[0], " slice"))
			obj->slice = stk(value);
		else if (obj->type != PARAPLOID && c == 2 && ck(s, " refl: ", 7) > 0 && !ft_strcmp(value[0], " refl"))
			obj->refl = abs(ft_atoi(value[1]));
		else if (obj->type != PARAPLOID && c == 2 && ck(s, " refr: ", 7) > 0 && !ft_strcmp(value[0], " refr"))
			obj->refr = abs(ft_atoi(value[1]));
		else if ((obj->type == PARAPLOID || obj->type == CONE) && c == 2 && ck(s, " angle: ", 8) > 0 && !ft_strcmp(value[0], " angle"))
			obj->angle = abs(ft_atoi(value[1]));
		else if ((obj->type == SPHERE || obj->type == CYLINDER) && c == 2 && ck(s, " radius: ", 9) > 0 && !ft_strcmp(value[0], " radius"))
			obj->radius = abs(ft_atoi(value[1]));
		else if (obj->type != PARAPLOID && obj->type != CUBE && c == 2 && ck(s, " matter: ", 9) > 0 && !ft_strcmp(value[0], " matter"))
			obj->matter = abs(ft_atoi(value[1]));
		else if (obj->type != PARAPLOID && c == 2 && ck(s, " per_refr: ", 11) > 0 && !ft_strcmp(value[0], " per_refr"))
			obj->per_refr = abs(ft_atoi(value[1]));
		else if (obj->type != PARAPLOID && obj->type != CUBE && c == 2 && ck(s, " neg_obj: ", 10) > 0 && !ft_strcmp(value[0], " neg_obj"))
			obj->neg_obj = abs(ft_atoi(value[1]));
		else if (obj->type != PARAPLOID && obj->type != CUBE && c == 4 && ck(s, " pos_slice: ", 12) > 0 && !ft_strcmp(value[0], " pos_slice"))
			obj->pos_slice = stk(value);
		else if (obj->type != PARAPLOID && c == 4 && ck(s, " pos_texture: ", 14) > 0 && !ft_strcmp(value[0], " pos_texture"))
			obj->pos_texture = stk(value);
		else if (c == 4 && ck(s, " center: ", 9) > 0 && !ft_strcmp(value[0], " center"))
			obj->center = stk(value);
		else if (obj->type != SPHERE && obj->type != CUBE && c == 4 && ck(s, " axis: ", 7) > 0 && !ft_strcmp(value[0], " axis"))
			obj->v = stk(value);	
		else if (c == 4 && ck(s, " rot: ", 6) > 0 && !ft_strcmp(value[0], " rot"))
			obj->rot = stk(value);
		else if (c == 4 && ck(s, " trs: ", 6) > 0 && !ft_strcmp(value[0], " trs"))
			obj->trs = stk(value);
		else if (c == 4 && ck(s, " color: ", 8) > 0 && !ft_strcmp(value[0], " color"))
			obj->color = checkcolorvalue(value);
		else
		{
			ft_strdel(&s);
			ft_strdel(value);
			return (-1);
		}
		ft_strdel(value);
		ft_strdel(&s);
	}
	return (1);
}

int	ck(char *s, char *check, int l)
{
	int		i;

	if (s[0] != ' ' || ft_strncmp(s, check, l) != 0)
	{
		return (-1);
	}
	// if (s[l] == '.')
	// 	return 1;
	i = l - 1;
	if ((s[l] < '0' || s[l] > '9') && s[l] != '-' && s[l] != '+')
		{
		return (-1);
	}
	while (s[i])
	{
		if (s[i] == '.')
			i++;
		if ((s[i] == ':' && s[i + 1] == ':')
			|| (s[i] == ':' && s[i + 1] == '\0')
			|| (s[i] == ':' && s[i + 1] == ' ')
			|| (s[i] == ' ' && s[i + 1] == '\0'))
			return (-1);
		else if (s[i] == ':' || s[i] == '-' || s[i] == '+' || s[i] == ' ')
		{
			if (s[i] == ':' && s[i + 1] == ':')
				return (-1);
		}
		else if (ft_isdigit(s[i]) == 0)
			return (-1);
		i++;
	}
	return (1);
}
