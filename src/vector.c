/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:49:55 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/10 13:59:39 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_vector	v_add(t_vector a, t_vector b)
{
	return ((t_vector){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vector	v_sub(t_vector a, t_vector b)
{
	return ((t_vector){a.x - b.x, a.y - b.y, a.z - b.z});
}

double	v_mag(t_vector *a, t_vector *b)
{
	double	res;

	res = sqrt(pow(b->x - a->x, 2) + pow(b->y - a->y, 2) + pow(b->z - a->z, 2));
	return (res);
}

double	v_dot(t_vector *a, t_vector *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_vector	v_norm(t_vector a)
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
