/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:22:16 by yataji            #+#    #+#             */
/*   Updated: 2021/03/04 14:07:22 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# define MAXWIDTH 700
# define MAXHEIGHT 700
# define SPHERE 0
# define CYLINDER 1
# define CONE 2

typedef struct 		s_vect {
	double 			x;
	double 			y;
	double 			z;
}					t_vect;

typedef t_vect	t_point;
typedef t_vect	t_color;

typedef struct		s_obj {
	int				type;
	double			angle;
	double			radius;
	t_vect			v;
	t_color			color;
	t_point			center;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_ray
{
	t_point			org;
	t_vect			dir;
	t_vect			hit;
}					t_ray;

typedef struct		s_math
{
	double			a;
	double			b;
	double			c;
	double			delta;
}					t_math;

typedef struct		s_mlx{
	void			*ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				*dtadd;
	int				bpp;
	int				szln; 
	int				end;
}					t_mlx;

typedef struct		s_cam
{
	t_point			lokat;
	t_point			lokfrm;
}					t_cam;

typedef struct		s_lights
{
	double			intensity;
	int				color;
	t_point			pos;
	struct s_lights	*next;
}					t_lights;

typedef struct		s_rtv1
{
	t_mlx			mlx;
	t_obj			*obj;
	t_ray			ray;
	t_cam			cam;
	t_lights		light;
	t_math			calc;
}				t_rtv1;

t_vect	plus(t_vect v1, t_vect v2);
t_vect	moins(t_vect v1, t_vect v2);
t_vect	multi(t_vect v1, double v2);
t_vect	normalize(t_vect v1);
t_vect	normsphr(t_ray *ray, t_obj *obj, double t);
t_vect	normcyld(t_ray *ray, t_obj *obj, double t);
t_vect  normcone(t_ray *ray, t_obj *obj, double t);
t_ray	initray(int x, int y);
t_mlx	init();
double	dot(t_vect a, t_vect b);
double	multidbl(double v1, double v2, double v3);
double	checkt(t_math calc);
double	intersect(t_obj *object, t_ray ray);
double	sphrintr(t_obj *sphere, t_ray ray);
double	cyldintr(t_obj *cyld, t_ray ray);
double	coneintr(t_obj *cone, t_ray ray);
int		keypress(int key, void *param);
int		ft_exit(t_mlx *mlx);
void	draw(t_rtv1 rt);

#endif
