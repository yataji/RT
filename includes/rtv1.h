/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:22:16 by yataji            #+#    #+#             */
/*   Updated: 2021/03/13 22:14:19 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
// # include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# define MAXWIDTH 900
# define MAXHEIGHT 900
# define SPHERE 0
# define CYLINDER 1
# define CONE 2
# define PLAN 3

typedef struct		s_var {
	int				x;
	int				y;
	double			t;
	double			near;
}					t_var;

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
	t_vect			normal;
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
	t_vect			v;
	t_vect			u;
	t_vect			w;
	double			fov;
	double			plnw;
	double			plnh;
}					t_cam;

typedef struct		s_lights
{
	double			intensity;
	t_color			color;
	t_point			pos;
	struct s_lights	*next;
}					t_lights;

typedef struct		s_rtv1
{
	t_mlx			mlx;
	t_obj			*obj;
	t_obj			*tmpo;
	t_ray			ray;
	t_cam			cam;
	t_lights		*lights;
	t_lights		*tmpl;
	t_math			calc;
	int				fd;
	int				check[2];
}				t_rtv1;

/*
///// rtv1 /////
*/

t_ray		initray(t_rtv1 rt, int x, int y);
t_mlx		init();
double		dot(t_vect a, t_vect b);
double		multidbl(double v1, double v2, double v3);
double		checkt(t_math calc);
double		intersect(t_obj *object, t_ray ray);
double		sphrintr(t_obj *sphere, t_ray ray);
double		cyldintr(t_obj *cyld, t_ray ray);
double		coneintr(t_obj *cone, t_ray ray);
double		planiter(t_obj *cone, t_ray ray);
int			keypress(int key, void *param);
int			ft_exit(t_mlx *mlx);
void    	setnormal(t_obj *close, t_ray *ray, double t);
void		initcamera(t_cam *cam);
void		draw(t_rtv1 rt);

/*
///// math /////
*/

t_vect		plus(t_vect v1, t_vect v2);
t_vect		moins(t_vect v1, t_vect v2);
t_vect		multi(t_vect v1, double v2);
t_vect		normalize(t_vect v1);
t_vect		normsphr(t_ray *ray, t_obj *obj, double t);
t_vect		normcyld(t_ray *ray, t_obj *obj, double t);
t_vect  	normcone(t_ray *ray, t_obj *obj, double t);
t_vect		crosspro(t_vect v1, t_vect v2);

/*
///// parsing /////
*/

t_lights	*initlights(void);
t_obj		*initobj(void);
t_vect		stk(char **value);
int			parse(t_rtv1*rt);
int			sphere(t_obj *obj, char *str, int fd);
int			plan(t_obj *obj, char *str, int fd);
int			cylinder(t_obj *obj, char *str, int fd);
int			cone(t_obj *obj, char *str, int fd);
int			lights(t_lights *lights, char *str, int fd);
int			camera(t_cam *cam, char *str, int fd);
int			checkval(char *str, char *check, int len);
int			ft_plan(t_rtv1 *rt, char *str);
int			ft_cone(t_rtv1 *rt, char *str);
int			ft_cylinder(t_rtv1 *rt, char *str);
int			ft_sphere(t_rtv1 *rt, char *str);
int			ft_lights(t_rtv1 *rt, char *str);
size_t		ft_strlend(char **s);

#endif
