/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:21:31 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/30 13:08:45 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	is_valid_ratio(char *str)
{
	float	input;

	input = ft_atof(str);
	if (input >= 0.0f && input <= 1.0f)
		return (TRUE);
	return (FALSE);
}

int	is_valid_rgb(char *str)
{
	int	col;
	
	col = ft_atoi(str);
	if (col >= 0 && col <= 255)
		return (TRUE);
	return (FALSE);
}
