/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathnorm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:26:30 by yataji            #+#    #+#             */
/*   Updated: 2021/03/10 18:29:32 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		multidbl(double v1, double v2, double v3)
{
	return (v1 * v2 * v3);
}

t_vect		multi(t_vect v1, double v2)
{
	t_vect	vctmlt;

	vctmlt.x = v1.x * v2;
	vctmlt.y = v1.y * v2;
	vctmlt.z = v1.z * v2;
	return (vctmlt);
}
