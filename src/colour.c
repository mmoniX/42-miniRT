/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:27:41 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/11 14:43:38 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_col	c_mult(t_col a, t_col b)
{
	t_col	out;

	out.red = (a.red * b.red) / 255.0;
	out.green = (a.green * b.green) / 255.0;
	out.blue = (a.blue * b.blue) / 255.0;
	return (out);
}

t_col	c_add(t_col a, t_col b)
{
	return ((t_col){a.red + b.red, a.green + b.green, a.blue + b.blue});
}

t_col	c_m_sca(t_col a, double n)
{
	return ((t_col){a.red * n, a.green * n, a.blue * n});
}
