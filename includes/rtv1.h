/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:22:16 by yataji            #+#    #+#             */
/*   Updated: 2021/02/25 16:29:00 by yataji           ###   ########.fr       */
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

typedef struct	s_vect3{
	double		x;
	double		y;
	double		z;
}				t_vect3;

typedef struct	s_ray{
	t_vect3		or;
	t_vect3		dir;
}				t_ray;

typedef struct	s_mlx{
	void		*ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*dtadd;
	int			bpp;
	int			szln; 
	int			end;
	t_ray		ray;
}				t_mlx;
#endif
