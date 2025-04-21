/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:09:34 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/21 18:14:10 by mmonika          ###   ########.fr       */
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
