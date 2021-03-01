/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:00:48 by yataji            #+#    #+#             */
/*   Updated: 2021/02/28 13:00:56 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int ft_pow(int x)
{
	return (x * x);
}

t_mlx init()
{
	t_mlx mlx;

	mlx.ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.ptr, MAXWIDTH, MAXHEIGHT, "rtv1");
	mlx.img_ptr = mlx_new_image(mlx.ptr, MAXWIDTH, MAXHEIGHT);
	mlx.dtadd = (int *)mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.szln, &mlx.end);
	return (mlx);
}

int ft_exit(t_mlx *mlx)
{
	mlx_clear_window(mlx->ptr, mlx->win_ptr);
	mlx_destroy_window(mlx->ptr, mlx->win_ptr);
	exit(0);
	return (0);
}

int keypress(int key, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	key == 53 ? ft_exit(mlx) : 0;
	return (0);
}

double dot(t_vect a, t_vect b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_ray initray(int x, int y)
{
	t_ray ray;

	ray.org = (t_point){x, y, 0};
	ray.dir = (t_vect){0, 0, 1};
	return (ray);
}

double checkt(t_math calc)
{
	double t1;
	double t2;

	if (calc.delta < 0)
		return (-1);
	else if (calc.delta == 0)
		return (-calc.b / (2 * calc.a));
	t1 = (-calc.b - sqrtf(calc.delta)) / (2 * calc.a);
	t2 = (-calc.b + sqrtf(calc.delta)) / (2 * calc.a);
	if (t1 < t2 && t1 >= 0)
		return (t1);
	else if (t2 >= 0)
		return (t2);
	return (-1);
}

double sphrintr(t_obj *sphere, t_ray ray)
{
	t_vect oc;
	t_math calc;

	oc = (t_vect){ray.org.x - sphere->center.x, ray.org.y - sphere->center.y, ray.org.z - sphere->center.z};
	calc.a = dot(ray.dir, ray.dir);
	calc.b = 2 * (ray.dir.x * oc.x + ray.dir.y * oc.y + ray.dir.z * oc.z);
	calc.c = (oc.x * oc.x + oc.y * oc.y + oc.z * oc.z) - (sphere->radius * sphere->radius);
	calc.delta = calc.b * calc.b - 4 * calc.a * calc.c;
	return (checkt(calc));
}

double	intersect(t_obj *object, t_ray ray)
{
	if (object->type == SPHERE)
		return (sphrintr(object, ray));
	return (-1);
}


t_vect	plus(t_vect v1, t_vect v2)
{
	t_vect	vctpls;
	
	vctpls.x = v1.x + v2.x;
	vctpls.y = v1.y + v2.y;
	vctpls.z = v1.z + v2.z;
	return (vctpls);
}

t_vect	multi(t_vect v1, double v2)
{
	t_vect	vctpls;
	
	vctpls.x = v1.x * v2;
	vctpls.y = v1.y * v2;
	vctpls.z = v1.z * v2;
	return (vctpls);
}

t_vect	normalize(t_vect v1)
{
	double v;
	
	v = sqrtf(dot(v1, v1));
	return (multi(v1, 1.0 / v));
}

t_vect	moins(t_vect v1, t_vect v2)
{
	t_vect	vctmns;
	
	vctmns.x = v1.x - v2.x;
	vctmns.y = v1.y - v2.y;
	vctmns.z = v1.z - v2.z;
	return (vctmns);
}

t_vect	normsphr(t_ray *ray, t_obj *obj, double t)
{
	t_vect	norm;

	ray->hit = plus(ray->org, multi(ray->dir, t));
	norm = moins(ray->hit, obj->center);
	norm = normalize(norm);
	return (norm);
}

void draw(t_rtv1 rt)
{
	int x;
	int y;
	double t;
	t_vect norm;
	t_obj *tmp;
	t_vect lightdir;

	x = -1;
	while (++x < MAXWIDTH)
	{
		y = -1;
		while (++y < MAXHEIGHT)
		{
			rt.ray = initray(x, y);
			tmp = rt.obj;
			while (tmp)
			{
				t = intersect(tmp, rt.ray);
				norm = normsphr(&rt.ray, tmp, t);
				if (t >= 0) 
				{
					lightdir = normalize(moins((t_vect){350, 350, 0}, rt.ray.hit));
					double dot1 = dot(norm, lightdir);
					dot1 < 0 || dot1 > 1 ? dot1 = 0 : 0;
					int color = 0;
					unsigned char *ptr = (unsigned char *)&color;
					ptr[0] = 255 * dot1;
					ptr[1] = 2 * dot1;
					ptr[2] = 2 * dot1;
					rt.mlx.dtadd[x + y * MAXWIDTH] = color;
				}
				else
					rt.mlx.dtadd[x + y * MAXWIDTH] = 0;
				tmp = tmp->next;
			}
		}
	}
	mlx_put_image_to_window(rt.mlx.ptr, rt.mlx.win_ptr, rt.mlx.img_ptr, 0, 0);
}

int main()
{
	t_rtv1 rt;

	rt.obj = (t_obj *)malloc(sizeof(t_obj));
	rt.obj->type = SPHERE;
	rt.obj->center = (t_point){350, 350, 220};
	rt.obj->radius = 200;
	rt.obj->next = NULL;
	rt.mlx = init();
	draw(rt);
	mlx_hook(rt.mlx.win_ptr, 2, 0, &keypress, &rt.mlx);
	mlx_loop(rt.mlx.ptr);
	return (0);
}
