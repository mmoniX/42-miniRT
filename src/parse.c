/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:56:55 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/27 18:20:18 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parsing(char *filename, t_map *map)
{
	int				fd;
	char			*line;
	char			**column;

	fd = open(filename, O_RDONLY);
	line = get_next_lin(fd);
	while (line)
	{
		column = ft_split(line, ' ');
		//TODO
		free_array(column);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
