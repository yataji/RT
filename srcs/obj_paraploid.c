/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_paraploid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:09:26 by jiqarbac          #+#    #+#             */
/*   Updated: 2021/04/20 01:47:52 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

int	ft_paraploid(t_rt *rt, char *str)
{
	rt->tmpo = initobj();
	if (paraploid(rt->tmpo, str, rt->fd) == -1)
		return (-1);
	rt->tmpo->next = rt->obj;
	rt->obj = rt->tmpo;
	return (0);
}

int	stockparaploid(t_obj *obj, char *str)
{
	char	**value;
	int		ck;

	value = ft_strsplit(str, ':');
	ck = ft_lendd(value);
	if (ck != 4 && ck != 2)
		return (-1);
	else if (ck == 4 && ft_strcmp(value[0], " center") == 0)
		obj->center = stk(value);
	else if (ck == 4 && ft_strcmp(value[0], " color") == 0)
		obj->color = checkcolorvalue(value);
	else if (ck == 2 && ft_strcmp(value[0], " radius") == 0)
		obj->radius = ft_atoi(value[1]);
	else if (ck == 4 && ft_strcmp(value[0], " axis") == 0)
		obj->v = stk(value);
	// else if (ck == 2 && ft_strcmp(value[0], " texture") == 0)
	// 	obj->text = ft_strdup(value[1]);
	else if (ck == 4 && ft_strcmp(value[0], " rot") == 0)
		obj->rot = stk(value);
	else if (ck == 4 && ft_strcmp(value[0], " trs") == 0)
		obj->trs = stk(value);
	else
	{
		ft_strdel(value);
		return (-1);
	}
	return (1);
}

int	paraploid(t_obj *obj, char *str, int fd)
{
	int		l;
	int		check;

	l = -1;
	while (++l < 7)
	{
		check = -1;
		if (get_next_line(fd, &str) < 0)
			return (-1);
		if (str && (ck(str, " center: ", 9) > 0 || ck(str, " radius: ", 9) > 0))
			check = stockparaploid(obj, str);
		else if (str && ck(str, " color: ", 8) > 0)
			check = stockparaploid(obj, str);
		else if (str && ck(str, " axis: ", 7) > 0)
			check = stockparaploid(obj, str);
		// else if (str && ck(str, " texture: ", 7) > 0)
		// 	check = textures(*obj);
		else if (str && (ck(str, " rot: ", 6) > 0 || ck(str, " trs: ", 6) > 0))
			check = stockparaploid(obj, str);
		if (check == -1)
			return (-1);
		obj->type = PARAPLOID;
		ft_strdel(&str);
	}
	// if (!checktext(obj->text))
		// return(-1);
	if (ft_strcmp(obj->texture, ".") != 0)
	{
		obj->surface = IMG_Load(obj->texture);
		if (!obj->surface)
			sdl_error("can't load surface");
	}
	obj->center = plus(obj->center, obj->trs);
	return (1);
}
