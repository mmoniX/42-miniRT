/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:55:14 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/09 16:05:27 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_vector	vector_mult_scalar(t_vector *a, double n)
{
	return ((t_vector){a->x * n, a->y * n, a->z * n});
}

t_vector	vector_cross(t_vector *a, t_vector *b)
{
	t_vector	res;

	res.x = (a->y * b->z) - (a->z * b->y);
	res.y = (a->z * b->x) - (a->x * b->z);
	res.z = (a->x * b->y) - (a->y * b->x);
	return (res);
}
