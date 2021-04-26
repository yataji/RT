/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:22:16 by yataji            #+#    #+#             */
/*   Updated: 2021/04/09 18:46:44 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# define MAXWIDTH 900
# define MAXHEIGHT 900
# define SPHERE 0
# define CYLINDER 1
# define CONE 2
# define PLANE 3

typedef struct s_var
{
	int				x;
	int				y;
	double			t;
	double			near;
}					t_var;

typedef struct s_vect
{
	double			x;
	double			y;
	double			z;
}					t_vect;

typedef t_vect		t_point;
typedef t_vect		t_color;
typedef t_vect		t_rot;

typedef struct s_obj
{
	int				type;
	double			angle;
	double			radius;
	t_vect			v;
	t_vect			normal;
	t_color			color;
	t_rot			rot;
	t_point			trs;
	t_point			center;
	struct s_obj	*next;
}					t_obj;

typedef struct s_ray
{
	t_point			org;
	t_vect			dir;
	t_vect			hit;
}					t_ray;

typedef struct s_math
{
	double			a;
	double			b;
	double			c;
	double			delta;
}					t_math;

typedef struct s_mlx
{
	void			*ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				*dtadd;
	int				bpp;
	int				szln;
	int				end;
}					t_mlx;

typedef struct s_cam
{
	t_point			lokat;
	t_point			lokfrm;
	t_vect			v;
	t_vect			u;
	t_vect			w;
	double			fov;
	double			plnw;
	double			plnh;
	struct s_cam	*next;
}					t_cam;

typedef struct s_lights
{
	double			intensity;
	t_color			color;
	t_point			pos;
	struct s_lights	*next;
}					t_lights;

typedef struct s_rtv1
{
	t_mlx			mlx;
	t_obj			*obj;
	t_obj			*tmpo;
	t_ray			ray;
	t_cam			*cam;
	t_cam			*tmpc;
	t_lights		*lights;
	t_lights		*tmpl;
	t_math			calc;
	unsigned char	*ptr;
	double			dot1;
	char			*str;
	int				fd;
	int				ck;
	int				color;
}					t_rtv1;

t_color				multi_color(t_color c1, double scal);
t_color				multi_tcolor(t_color c1, t_color c2);
t_color				add_color(t_color c1, t_color c2);
t_vect				rotation_xyz(t_vect v, t_vect a);
t_ray				initray(t_cam *cam, int x, int y);
t_mlx				init(void);
double				max(double v1, double v2);
double				dot(t_vect a, t_vect b);
double				multidbl(double v1, double v2, double v3);
double				checkt(t_math calc);
double				intersect(t_obj *object, t_ray ray);
double				sphrintr(t_obj *sphere, t_ray ray);
double				cyldintr(t_obj *cyld, t_ray ray);
double				coneintr(t_obj *cone, t_ray ray);
double				planiter(t_obj *cone, t_ray ray);
int					keypress(int key, void *param);
int					ft_exit(t_rtv1 *rt);
void				setnormal(t_obj *close, t_ray *ray, double t);
void				initcamera(t_cam *cam);
void				draw(t_rtv1 rt);
void				ft_free(t_obj **obj, t_lights **lights, t_cam **cam);
t_vect				plus(t_vect v1, t_vect v2);
t_vect				moins(t_vect v1, t_vect v2);
t_vect				multi(t_vect v1, double v2);
t_vect				normalize(t_vect v1);
t_vect				normsphr(t_ray *ray, t_obj *obj, double t);
t_vect				normcyld(t_ray *ray, t_obj *obj, double t);
t_vect				normcone(t_ray *ray, t_obj *obj, double t);
t_vect				crosspro(t_vect v1, t_vect v2);
t_lights			*initlights(void);
t_obj				*initobj(void);
t_cam				*initcam(void);
t_vect				stk(char **value);
size_t				ft_strlend(char **s);
t_color				checkcolorvalue(char **value);
int					parse(t_rtv1*rt);
int					sphere(t_obj *obj, char *str, int fd);
int					plane(t_obj *obj, char *str, int fd);
int					cylinder(t_obj *obj, char *str, int fd);
int					cone(t_obj *obj, char *str, int fd);
int					lights(t_lights *lights, char *str, int fd);
int					camera(t_cam *cam, char *str, int fd);
int					ck(char *str, char *check, int len);
int					chkone(char *str, int len);
int					ft_plane(t_rtv1 *rt, char *str);
int					ft_cone(t_rtv1 *rt, char *str);
int					ft_cylinder(t_rtv1 *rt, char *str);
int					ft_sphere(t_rtv1 *rt, char *str);
int					ft_lights(t_rtv1 *rt, char *str);
int					ft_cam(t_rtv1 *rt, char *str);

#endif