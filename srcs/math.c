/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:34:09 by yataji            #+#    #+#             */
/*   Updated: 2021/03/01 18:13:32 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect	plus(t_vect v1, t_vect v2)
{
	t_vect	vctpls;
	
	vctpls.x = v1.x + v2.x;
	vctpls.y = v1.y + v2.y;
	vctpls.z = v1.z + v2.z;
	return (vctpls);
}

t_vect	multi(t_vect v1, double v2)
{
	t_vect	vctmlt;
	
	vctmlt.x = v1.x * v2;
	vctmlt.y = v1.y * v2;
	vctmlt.z = v1.z * v2;
	return (vctmlt);
}

t_vect	multivect(t_vect v1, t_vect v2)
{
	t_vect	vctvect;
	
	vctvect.x = v1.x * v2.x;
	vctvect.y = v1.y * v2.y;
	vctvect.z = v1.z * v2.z;
	return (vctvect);
}


double	multidbl(double v1, double v2, double v3)
{
	return (v1 * v2 * v3);
}

double dot(t_vect a, t_vect b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vect	moins(t_vect v1, t_vect v2)
{
	t_vect	vctmns;
	
	vctmns.x = v1.x - v2.x;
	vctmns.y = v1.y - v2.y;
	vctmns.z = v1.z - v2.z;
	return (vctmns);
}