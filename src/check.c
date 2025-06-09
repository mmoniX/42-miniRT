/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:21:31 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/09 15:34:03 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static int	validate_mandatories(int fd)
{
	char	*line;
	int		amb_count;
	int		cam_count;
	int		light_count;

	amb_count = 0;
	cam_count = 0;
	light_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 'A' && (line[1] == ' ' || line[1] == '\t'))
			amb_count++;
		else if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
			cam_count++;
		else if (line[0] == 'L' && (line[1] == ' ' || line[1] == '\t'))
			light_count++;
		free(line);
	}
	if (amb_count != 1 || cam_count != 1 || light_count != 1)
	{
		ft_putstr_fd("Error: multiple A, C or L \n", STDERR_FILENO);
		return (FAIL);
	}
	return (SUCCESS);
}

int	check_file(char *filename)
{
	int	len;
	int	fd;

	len = ft_strlen(filename);
	if (!filename || len < 4)
		return (FAIL);
	if (ft_strncmp(filename + len - 3, ".rt", 3) != 0)
	{
		perror(filename);
		return (FAIL);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (FAIL);
	}
	if (validate_mandatories(fd) < 1)
		return (FAIL);
	close(fd);
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