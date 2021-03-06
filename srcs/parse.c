/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:01:53 by yataji            #+#    #+#             */
/*   Updated: 2021/03/06 07:43:17 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

size_t ft_strlend(char **s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int checkval(char *str, char *check, int len)
{
	int i;

	if (str[0] != '\t')
	{
		return (-1);
	}
	if (ft_strncmp(str, check, len) != 0)
	{
		return (-1);
	}
	i = len - 1;
	while (str[i])
	{
		if (str[i] == ':' && str[i + 1] == ':')
			return (-1);
		if (str[i] == ':' || str[i] == ' ' || str[i] == '\t')
			i++;
		if (ft_isdigit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (1);
}

int camera(t_cam *cam, char *str, int fd)
{
	char **value;
	int i;
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
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			cam->lokat.x = ft_atoi(value[1]);
			cam->lokat.y = ft_atoi(value[2]);
			cam->lokat.z = ft_atoi(value[3]);
		}
		else if (checkval(str, "\tlokfrm: ", 9) > 0 || checkval(str, "\tlokfrm:\t", 9) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			cam->lokfrm.x = ft_atoi(value[1]);
			cam->lokfrm.y = ft_atoi(value[2]);
			cam->lokfrm.z = ft_atoi(value[3]);
		}
		else
			return (-1);
	}
	return (1);
}

int lights(t_lights *lights, char *str, int fd)
{
	char **value;
	int i;
	int l;

	l = 0;
	while (l < 3)
	{
		if (get_next_line(fd, &str) < 0)
			return (-1);
		l++;
		if (checkval(str, "\tintensity: ", 12) > 0 || checkval(str, "\tintensity:\t", 12) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 2)
				return (-1);
			lights->intensity = ft_atoi(value[1]);
		}
		else if (checkval(str, "\tcolor: ", 8) > 0 || checkval(str, "\tcolor:\t", 8) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			lights->color.x = ft_atoi(value[1]);
			lights->color.y = ft_atoi(value[2]);
			lights->color.z = ft_atoi(value[3]);
		}
		else if (checkval(str, "\tpos: ", 6) > 0 || checkval(str, "\tpos:\t", 6) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			lights->pos.x = ft_atoi(value[1]);
			lights->pos.y = ft_atoi(value[2]);
			lights->pos.z = ft_atoi(value[3]);
		}
		else
			return (-1);
	}
	return (1);
}

int sphere(t_obj *obj, char *str, int fd)
{
	char **value;
	int i;
	int l;

	l = 0;
	while (l < 3)
	{
		if (get_next_line(fd, &str) < 0)
			return (-1);
		l++;
		if (checkval(str, "\tcenter: ", 9) > 0 || checkval(str, "\tcenter:\t", 9) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			obj->center.x = ft_atoi(value[1]);
			obj->center.y = ft_atoi(value[2]);
			obj->center.z = ft_atoi(value[3]);
		}
		else if (checkval(str, "\tcolor: ", 8) > 0 || checkval(str, "\tcolor:\t", 8) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			obj->color.x = ft_atoi(value[1]);
			obj->color.y = ft_atoi(value[2]);
			obj->color.z = ft_atoi(value[3]);
		}
		else if (checkval(str, "\tradius: ", 9) > 0 || checkval(str, "\tradius:\t", 9) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 2)
				return (-1);
			obj->radius = ft_atoi(value[1]);
		}
		else
			return (-1);
		obj->type = 0;
		obj->v = (t_vect){0, 0, 0};
		obj->angle = 0;
	}
	return (1);
}

int cylinder(t_obj *obj, char *str, int fd)
{
	char **value;
	int i;
	int l;

	l = 0;
	while (l < 4)
	{
		if (get_next_line(fd, &str) < 0)
			return (-1);
		l++;
		if (checkval(str, "\tcenter: ", 9) > 0 || checkval(str, "\tcenter:\t", 9) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			obj->center.x = ft_atoi(value[1]);
			obj->center.y = ft_atoi(value[2]);
			obj->center.z = ft_atoi(value[3]);
		}
		else if (checkval(str, "\tcolor: ", 8) > 0 || checkval(str, "\tcolor:\t", 8) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			obj->color.x = ft_atoi(value[1]);
			obj->color.y = ft_atoi(value[2]);
			obj->color.z = ft_atoi(value[3]);
		}
		else if (checkval(str, "\tradius: ", 9) > 0 || checkval(str, "\tradius:\t", 9) > 0)
		{
			value = ft_strsplit(str, ':');

			free(str);
			if (ft_strlend(value) != 2)
				return (-1);
			obj->radius = ft_atoi(value[1]);
		}
		else if (checkval(str, "\taxis: ", 7) > 0 || checkval(str, "\taxis:\t", 7) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			obj->v.x = ft_atoi(value[1]);
			obj->v.y = ft_atoi(value[2]);
			obj->v.z = ft_atoi(value[3]);
		}
		else
			return (-1);
		obj->type = 1;
		obj->angle = 0;
	}
	return (1);
}

int plan(t_obj *obj, char *str, int fd)
{
	char **value;
	int i;
	int l;

	l = 0;
	while (l < 4)
	{
		if (get_next_line(fd, &str) < 0)
			return (-1);
		l++;
		if (checkval(str, "\tcenter: ", 9) > 0 || checkval(str, "\tcenter:\t", 9) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			obj->center.x = ft_atoi(value[1]);
			obj->center.y = ft_atoi(value[2]);
			obj->center.z = ft_atoi(value[3]);
		}
		else if (checkval(str, "\tcolor: ", 8) > 0 || checkval(str, "\tcolor:\t", 8) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			obj->color.x = ft_atoi(value[1]);
			obj->color.y = ft_atoi(value[2]);
			obj->color.z = ft_atoi(value[3]);
		}
		else if (checkval(str, "\tradius: ", 9) > 0 || checkval(str, "\tradius:\t", 9) > 0)
		{
			value = ft_strsplit(str, ':');

			free(str);
			if (ft_strlend(value) != 2)
				return (-1);
			obj->radius = ft_atoi(value[1]);
		}
		else if (checkval(str, "\taxis: ", 7) > 0 || checkval(str, "\taxis:\t", 7) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			obj->v.x = ft_atoi(value[1]);
			obj->v.y = ft_atoi(value[2]);
			obj->v.z = ft_atoi(value[3]);
		}
		else
			return (-1);
		obj->type = 3;
		obj->angle = 0;
	}
	return (1);
}

int cone(t_obj *obj, char *str, int fd)
{
	char **value;
	int i;
	int l;

	l = 0;
	while (l < 4)
	{
		if (get_next_line(fd, &str) < 0)
			return (-1);
		l++;
		if (checkval(str, "\tcenter: ", 9) > 0 || checkval(str, "\tcenter:\t", 9) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			obj->center.x = ft_atoi(value[1]);
			obj->center.y = ft_atoi(value[2]);
			obj->center.z = ft_atoi(value[3]);
		}
		else if (checkval(str, "\tcolor: ", 8) > 0 || checkval(str, "\tcolor:\t", 8) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			obj->color.x = ft_atoi(value[1]);
			obj->color.y = ft_atoi(value[2]);
			obj->color.z = ft_atoi(value[3]);
		}
		else if (checkval(str, "\tangle: ", 8) > 0 || checkval(str, "\tangle:\t", 8) > 0)
		{
			value = ft_strsplit(str, ':');

			free(str);
			if (ft_strlend(value) != 2)
				return (-1);
			obj->angle = ft_atoi(value[1]);
		}
		else if (checkval(str, "\taxis: ", 7) > 0 || checkval(str, "\taxis:\t", 7) > 0)
		{
			value = ft_strsplit(str, ':');
			free(str);
			if (ft_strlend(value) != 4)
				return (-1);
			obj->v.x = ft_atoi(value[1]);
			obj->v.y = ft_atoi(value[2]);
			obj->v.z = ft_atoi(value[3]);
		}
		else
			return (-1);
		obj->type = 2;
		obj->radius = 0;
	}
	return (1);
}

int parse(t_rtv1 *rt)
{
	char *str;
	int fd;
	t_lights *tmpl;
	t_obj *tmpo;
	int i = 0;
	// int j = 0;
	fd = open("../rtv1.yaml", O_RDONLY);
	while (fd > 2 && get_next_line(fd, &str) > 0)
	{
		if (ft_strcmp(str, "camera:") == 0)
		{
			if (camera(&rt->cam, str, fd) == -1)
			{
				printf(";;\n");
				return (-1);
			}
			// j++;
		}
		else if (ft_strcmp(str, "lights:") == 0)
		{
			tmpl = (t_lights *)malloc(sizeof(t_lights));
			if (i > 0)
			{
				if (lights(tmpl, str, fd) == -1)
					return (-1);
			}
			else if (lights(tmpl, str, fd) == -1)
				return (-1);
			i++;
			tmpl->next = rt->lights;
			rt->lights = tmpl;
		}
		else if (ft_strcmp(str, "sphere:") == 0)
		{
			tmpo = (t_obj *)malloc(sizeof(t_obj));
			if (i > i + 1)
			{
				if (sphere(tmpo, str, fd) == -1)
					return (-1);
			}
			if (sphere(tmpo, str, fd) == -1)
				return (-1);
			i++;
			tmpo->next = rt->obj;
			rt->obj = tmpo;
		}
		if (ft_strcmp(str, "cylinder:") == 0)
		{
			tmpo = (t_obj *)malloc(sizeof(t_obj));
			if (i > i + 1)
			{
				if (cylinder(tmpo, str, fd) == -1)
					return (-1);
			}
			if (cylinder(tmpo, str, fd) == -1)
				return (-1);
			i++;
			tmpo->next = rt->obj;
			rt->obj = tmpo;
		}
		if (ft_strcmp(str, "cone:") == 0)
		{
			tmpo = (t_obj *)malloc(sizeof(t_obj));
			if (i > i + 1)
			{
				if (cone(tmpo, str, fd) == -1)
					return (-1);
			}
			if (cone(tmpo, str, fd) == -1)
				return (-1);
			i++;
			tmpo->next = rt->obj;
			rt->obj = tmpo;
		}
		if (ft_strcmp(str, "plan:") == 0)
		{
			tmpo = (t_obj *)malloc(sizeof(t_obj));
			if (i > i + 1)
			{
				if (plan(tmpo, str, fd) == -1)
					return (-1);
			}
			if (plan(tmpo, str, fd) == -1)
				return (-1);
			i++;
			tmpo->next = rt->obj;
			rt->obj = tmpo;
		}
		else
			return (-1);
	}
	return (1);
}

int main()
{
	t_rtv1 rt, tmp;
	rt.lights = NULL;
	rt.obj = NULL;
	if (parse(&rt) != -1)
		return (0);
	tmp = rt;
	printf("x: %lf\ty: %lf\tz: %lf\n", rt.cam.lokat.x, rt.cam.lokat.y, rt.cam.lokat.z);
	printf("x: %lf\ty: %lf\tz: %lf\n", rt.cam.lokfrm.x, rt.cam.lokfrm.y, rt.cam.lokfrm.z);
	while (rt.lights)
	{
		// printf("intensity: %lf\tcolor: %d\tpos.x: %lf\tpos.y: %lf\tpos.z: %lf\n", rt.lights->intensity, rt.lights->color, rt.lights->pos.x, rt.lights->pos.y, rt.lights->pos.z);
		printf("intensity: %lf\tcolor.x: %lf\tcolor.y: %lf\tcolor.z: %lf\tpos.x: %lf\tpos.y: %lf\tpos.z: %lf\n", rt.lights->intensity, rt.lights->color.x, rt.lights->color.y, rt.lights->color.z, rt.lights->pos.x, rt.lights->pos.y, rt.lights->pos.z);
		rt.lights = rt.lights->next;
	}
	while (rt.obj)
	{
		printf("center.x: %lf\tcenter.y: %lf\tcenter.z: %lf\tcolor.x: %lf\tcolor.y: %lf\tcolor.z: %lf\tradius: %lf\taxis.x: %lf\taxis.y: %lf\taxis.z: %lf\tangle: %lf\ttype: %d\n", rt.obj->center.x, rt.obj->center.y, rt.obj->center.z, rt.obj->color.x, rt.obj->color.y, rt.obj->color.z, rt.obj->radius, rt.obj->v.x, rt.obj->v.y, rt.obj->v.z, rt.obj->angle, rt.obj->type);
		rt.obj = rt.obj->next;
	}
	return (0);
}
