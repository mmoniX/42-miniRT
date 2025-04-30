/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:55:14 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/29 16:55:47 by mmonika          ###   ########.fr       */
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
