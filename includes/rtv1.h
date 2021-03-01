/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:22:16 by yataji            #+#    #+#             */
/*   Updated: 2021/02/28 12:15:06 by yataji           ###   ########.fr       */
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

#endif
