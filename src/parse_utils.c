/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:49:47 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/30 18:45:15 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_vector	parse_point(char *tokens)
{
	t_vector	point;
	char		**pos;

	pos = ft_split(tokens, ',');
	if (!pos[0] || !pos[1] || !pos[2])
	{
		perror("Error: parse point");
		exit (1);
	}
	point.x = ft_atof(pos[0]);
	point.y = ft_atof(pos[1]);
	point.z = ft_atof(pos[2]);
	free_array(pos);
	return (point);
}

t_col	parse_color(char *tokens)
{
	t_col	color;
	char	**rgb;

	rgb = ft_split(tokens, ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		perror("Error: parse color");
		exit (1);
	}
	color.red = ft_atoi(rgb[0]);
	color.green = ft_atoi(rgb[1]);
	color.blue = ft_atoi(rgb[2]);
	free_array(rgb);
	return (color);
}

void	parse_ambient(char **tokens, t_mrt *mrt)
{
	if (!tokens[1] || !tokens[2])
	{
		perror("Error: amb token");
		exit(1);
	}
	mrt->amb.ratio = ft_atof(tokens[1]);
	mrt->amb.color = parse_color(tokens[2]);
}

void	parse_camera(char **tokens, t_mrt *mrt)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		perror("Error: camera token");
		exit(1);
	}
	mrt->camera.position = parse_point(tokens[1]);
	mrt->camera.normal = parse_point(tokens[2]);
	mrt->camera.fov = ft_atof(tokens[3]);
}

void	parse_light(char **tokens, t_mrt *mrt)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		perror("Error: light token");
		exit(1);
	}
	mrt->light.position = parse_point(tokens[1]);
	mrt->light.brightness = ft_atof(tokens[2]);
	mrt->light.color = parse_color(tokens[3]);
}

void	parsing(char *filename, t_mrt *mrt)
{
	int				fd;
	char			*line;
	char			**tokens;

	fd = open(filename, O_RDONLY);
	if(fd < 0)
		return (perror("fd failed"));
	while ((line = get_next_line(fd)))
	{
		if(*line == '\0' || line[0] == '\n')
		{
			free(line);
			continue;
		}
		tokens = ft_split(normalize_whitespace(line), ' ');
		if (!tokens || !tokens[0])
		{
			free(line);
			continue;
		}
		if (ft_strcmp(tokens[0], "A") == 0)
			parse_ambient(tokens, mrt);
		if (ft_strcmp(tokens[0], "C") == 0)
			parse_camera(tokens, mrt);
		if (ft_strcmp(tokens[0], "L") == 0)
			parse_light(tokens, mrt);
		if (ft_strcmp(tokens[0], "pl") == 0)
			parse_plane(tokens, mrt);
		if (ft_strcmp(tokens[0], "sp") == 0)
			parse_sphere(tokens, mrt);
		if (ft_strcmp(tokens[0], "cy") == 0)
			parse_cylinder(tokens, mrt);
		free_array(tokens);
		free(line);
	}
	close(fd);
}
