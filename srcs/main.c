/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:00:48 by yataji            #+#    #+#             */
/*   Updated: 2021/02/25 19:31:26 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int	ft_pow(int x)
{
	return (x * x);
}

t_mlx	init()
{
	t_mlx	mlx;

	mlx.ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.ptr, MAXWIDTH, MAXHEIGHT, "rtv1");
	mlx.img_ptr = mlx_new_image(mlx.ptr, MAXWIDTH, MAXHEIGHT);
	mlx.dtadd = (int *)mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.szln, &mlx.end);
	return (mlx);
}

int					ft_exit(t_mlx *mlx)
{
	mlx_clear_window(mlx->ptr, mlx->win_ptr);
	mlx_destroy_window(mlx->ptr, mlx->win_ptr);
	exit(0);
	return (0);
}

int			keypress(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	key == 53 ? exit(0) : 0;
	return (0);
}

typedef struct s_vect {
	double x;
	double y;
	double z;
}				t_vect;

void	draw(t_mlx *mlx)
{
	int		x;
	int		y;
	int		z;

	t_vect	center = (t_vect){350, 350, -500};
	double	rayon = 60;
	t_vect	org;
	t_vect	dir = (t_vect){0, 0, -1};
	z = 0;
	x = -1;
	while (++x < MAXWIDTH)
	{
		y = -1;
		while (++y < MAXHEIGHT)
		{
			double t = -1;
			org = (t_vect){x, y, 0};
			double a = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
			double b = 2 * (dir.x * (org.x - center.x) + dir.y * (org.y - center.y) + dir.z * (org.z - center.z));
			double c = ((org.x - center.x) * (org.x - center.x) + (org.y - center.y) * (org.y - center.y) + (org.z - center.z) * (org.z - center.z)) - (rayon * rayon);
			double delta = b * b - 4.0 * a * c;
			if (delta > 0)
				t = (- b + sqrtf(delta)) / 2 * a;
			if (delta == 0)
				t = -b / 2 *a;
			if (t < 0)
				mlx->dtadd[x + y * MAXWIDTH] = 0X00;
			else
				mlx->dtadd[x + y * MAXWIDTH] = 0Xff;
		}
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	mlx_hook(mlx->win_ptr, 2, 0, &keypress, &mlx);
	mlx_loop(mlx->ptr);
}

int		main()
{
	t_mlx	mlx;

	mlx = init();
	draw(&mlx);
	return (0);
}
