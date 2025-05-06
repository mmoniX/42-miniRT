/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:55:14 by mmonika           #+#    #+#             */
/*   Updated: 2025/05/06 20:18:09 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_vector	vector_multiplication(t_vector *a, double n)
{
	t_vector	res;

	res.x = a->x * n;
	res.y = a->y * n;
	res.z = a->z * n;
	return (res);
}

t_vector	vector_cross(t_vector *a, t_vector *b)
{
	t_vector	res;
	
	res.x = (a->y * b->z) - (a->z * b->y);
	res.y = (a->z * b->x) - (a->x * b->z);
	res.z = (a->x * b->y) - (a->y * b->x);
	return (res);
}
