/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:20:48 by yataji            #+#    #+#             */
/*   Updated: 2021/02/24 17:08:56 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

//center x y
// rayon
//color
// (x - xc)^2 + (y - yc)^2 = R^2

double ft_pow(double x)
{
    return (x * x);
}

t_ray newray(int x, int y, int z)
{
    t_ray new;
    new.or.x = x;
    new.or.y = y;
    new.or.z = z;
    new.dir.x = 0;
    new.dir.y = 0;
    new.dir.z = 1;
    return (new);
}

int main(void)
{
    int tab[3];
    void *mlxptr = mlx_init();
    void *winptr = mlx_new_window(mlxptr,500,500,"test");
    void *imgptr = mlx_new_image(mlxptr,500,500);
    int *imgdata = (int*)mlx_get_data_addr(imgptr,&tab[0],&tab[1],&tab[2]);
    int x = 0;
    int y;
    int z = 0;
    while(x < 500)
    {
        y = 0;
        while (y < 500)
        {
            if(ft_pow(x - 250) + ft_pow(y - 250) + ft_pow(z - 101) <= ft_pow(100))
                imgdata[x + y * MAX] = 0Xff;
            else
                imgdata[x + y * 500] = 0X0;
            y++;
        }
       x++;
    }
    mlx_put_image_to_window(mlxptr,winptr,imgptr,0,0);
    mlx_loop(mlxptr);
}
