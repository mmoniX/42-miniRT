/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:49:55 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/09 15:11:52 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_vector	vector_addition(t_vector *a, t_vector *b)
{
	return ((t_vector){a->x + b->x, a->y + b->y, a->z + b->z});
}

t_vector	vector_subtraction(t_vector *a, t_vector *b)
{
	return ((t_vector){a->x - b->x, a->y - b->y, a->z - b->z});
}

double	vector_magnitude(t_vector *a, t_vector *b)
{
	double	res;

	res = sqrt(pow(b->x - a->x, 2) + pow(b->y - a->y, 2) + pow(b->z - a->z, 2));
	return (res);
}

double	vector_dot(t_vector *a, t_vector *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_vector	vector_normalization(t_vector a)
{
	t_vector	res;
	double		magnitude;

	magnitude = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
	if (magnitude == 0)
	{
		ft_putstr_fd("Division by zero in vector normalization", STDERR_FILENO);
		return ((t_vector){0, 0, 0});
	}
	res.x = a.x / magnitude;
	res.y = a.y / magnitude;
	res.z = a.z / magnitude;
	return (res);
}
