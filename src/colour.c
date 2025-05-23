/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:27:41 by mmonika           #+#    #+#             */
/*   Updated: 2025/05/24 17:20:42 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// double	overflow_cap(double c)
// {
// 	if (c < 0)
// 		return (0);
// 	if (c > 1)
// 		return (1);
// 	return (c);
// }

t_col color_mult(t_col a, t_col b)
{
	t_col	out;
	out.red = (a.red * b.red) / 255.0;
	out.green = (a.green * b.green) / 255.0;
	out.blue = (a.blue * b.blue) / 255.0;
	return (out);
}

t_col	color_add(t_col *a, t_col *b)
{
	return ((t_col){a->red + b->red, a->green + b->green, a->blue + b->blue});
}