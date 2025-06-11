/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:49:47 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/11 14:02:41 by mmonika          ###   ########.fr       */
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
		ft_putstr_fd("Error: parse point", STDERR_FILENO);
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
		ft_putstr_fd("Error: parse color", STDERR_FILENO);
		free_array(rgb);
		exit (1);
	}
	color.red = ft_atoi(rgb[0]);
	color.green = ft_atoi(rgb[1]);
	color.blue = ft_atoi(rgb[2]);
	if (!is_valid_rgb(color, 0, 255))
	{
		ft_putstr_fd("Error: invalid RGB value", STDERR_FILENO);
		free_array(rgb);
		exit(1);
	}
	free_array(rgb);
	return (color);
}

void	parse_ambient(char **tokens, t_mrt *mrt)
{
	if (!tokens[1] || !tokens[2])
	{
		ft_putstr_fd("Error: amb token", STDERR_FILENO);
		exit(1);
	}
	mrt->amb.ratio = ft_atof(tokens[1]);
	if (mrt->amb.ratio < 0.0f || mrt->amb.ratio > 1.0f)
	{
		ft_putstr_fd("Error: amb Ratio out of range", STDERR_FILENO);
		exit(1);
	}
	mrt->amb.color = parse_color(tokens[2]);
}

void	parse_camera(char **tokens, t_mrt *mrt)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		ft_putstr_fd("Error: camera token", STDERR_FILENO);
		exit(1);
	}
	mrt->camera.position = parse_point(tokens[1]);
	mrt->camera.normal = parse_point(tokens[2]);
	if (!is_valid_normal(mrt->camera.normal, -1, 1))
	{
		ft_putstr_fd("Error: camera Norm out of range", STDERR_FILENO);
		exit(1);
	}
	mrt->camera.fov = ft_atof(tokens[3]);
	if (mrt->camera.fov < 0 || mrt->camera.fov > 180)
	{
		perror("Error: camera FOV out of range");
		exit(1);
	}
}

void	parse_light(char **tokens, t_mrt *mrt)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		ft_putstr_fd("Error: light token", STDERR_FILENO);
		exit(1);
	}
	mrt->light.position = parse_point(tokens[1]);
	mrt->light.brightness = ft_atof(tokens[2]);
	if (mrt->light.brightness < 0.0f || mrt->light.brightness > 1.0f)
	{
		ft_putstr_fd("Error: light's Brightness out of range", STDERR_FILENO);
		exit(1);
	}
	mrt->light.color = parse_color(tokens[3]);
}
