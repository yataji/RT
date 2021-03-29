/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:48:53 by jiqarbac          #+#    #+#             */
/*   Updated: 2021/03/29 14:48:55 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect		stk(char **value)
{
	t_vect	new;

	new.x = ft_atoi(value[1]);
	new.y = ft_atoi(value[2]);
	new.z = ft_atoi(value[3]);
	return (new);
}
