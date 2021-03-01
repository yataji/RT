/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:22:16 by yataji            #+#    #+#             */
/*   Updated: 2021/03/01 19:07:29 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# define MAXWIDTH 700
# define MAXHEIGHT 700
# define SPHERE 0
# define CYLINDER 1

typedef struct 		s_vect {
	double 			x;
	double 			y;
	double 			z;
}					t_vect;

typedef t_vect t_point;

typedef struct		s_obj {
	int				type;
	double			radius;
	t_point			center;
	struct s_obj	*next;
}					t_obj;

typedef struct	s_ray
{
	t_point			org;
	t_vect			dir;
	t_vect			hit;
}				t_ray;

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

typedef struct s_rtv1
{
	t_mlx	mlx;
	t_obj	*obj;
	t_ray	ray;
	t_math	calc;
}				t_rtv1;

t_vect	plus(t_vect v1, t_vect v2);
t_vect	moins(t_vect v1, t_vect v2);
t_vect	multi(t_vect v1, double v2);
t_vect	normalize(t_vect v1);
t_ray	initray(int x, int y);
t_mlx	init();
double	dot(t_vect a, t_vect b);
double	multidbl(double v1, double v2, double v3);
double	checkt(t_math calc);
double	intersect(t_obj *object, t_ray ray);
double	sphrintr(t_obj *sphere, t_ray ray);
double	cyldintr(t_obj *cyld, t_ray ray);
int		keypress(int key, void *param);
int		ft_exit(t_mlx *mlx);
void	drawsphr(t_rtv1 rt);

#endif
