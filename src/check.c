/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:21:31 by mmonika           #+#    #+#             */
/*   Updated: 2025/05/27 13:07:05 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	check_file(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (!filename || len < 4)
		return (FAIL);
	if (ft_strncmp(filename + len - 3, ".rt", 3) != 0)
	{
		perror(filename);
		return (FAIL);
	}
	return (SUCCESS);
}

int	is_valid_normal(t_vector vec, float min, float max)
{
	return (vec.x >= min && vec.x <= max
		&& vec.y >= min && vec.y <= max
		&& vec.z >= min && vec.z <= max);
}

int	is_valid_rgb(t_col col, int min, int max)
{
	return (col.red >= min && col.red <= max
		&& col.green >= min && col.green <= max
		&& col.blue >= min && col.blue <= max);
}

// * 2. checking if file is not empty or only empty lines
// * 3. check if all mandadory object occurs exact 1 time A, C, L
// * 4. check valid path