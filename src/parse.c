/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:56:55 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/30 16:56:13 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parse_ambient(char **tokens, t_mrt *mrt)
{
	char	**rgb;
	
	if(!tokens[1] || !tokens[2])
	{
		perror("Error: amb token");
		exit(1);
	}
	mrt->amb.ratio = atof(tokens[1]);
	rgb = ft_split(tokens[2], ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		perror("Error: amb color");
		exit (1);
	}
	mrt->amb.color.red = ft_atoi(rgb[0]);
	mrt->amb.color.green = ft_atoi(rgb[1]);
	mrt->amb.color.blue = ft_atoi(rgb[2]);
	free_array(rgb); //free array
}

void	parse_camera(char **tokens, t_mrt *mrt)
{
	char **pos;
	char **norm;
	if(!tokens[1] || !tokens[2] || !tokens[3])
	{
		perror("Error: camera token");
		exit(1);
	}
	pos = ft_split(tokens[1], ',');
	if (!pos[0] || !pos[1] || !pos[2])
	{
		perror("Error: camera position");
		exit (1);
	}
	mrt->camera.position.x = atof(pos[0]);
	mrt->camera.position.y = atof(pos[1]);
	mrt->camera.position.z = atof(pos[2]);
	norm = ft_split(tokens[2], ',');
	if (!norm[0] || !norm[1] || !norm[2])
	{
		perror("Error: camera normal");
		exit (1);
	}
	mrt->camera.normal.x = atof(norm[0]);
	mrt->camera.normal.y = atof(norm[1]);
	mrt->camera.normal.z = atof(norm[2]);
	mrt->camera.fov = atof(tokens[3]);
	free_array(pos);
	free_array(norm);
}
void	parse_light(char **tokens, t_mrt *mrt)
{
	char	**pos;
	char	**rgb;
	
	if(!tokens[1] || !tokens[2] || !tokens[3])
	{
		perror("Error: light token");
		exit(1);
	}
	pos = ft_split(tokens[1], ',');
	if (!pos[0] || !pos[1] || !pos[2])
	{
		perror("Error: light position");
		exit (1);
	}
	mrt->light.position.x = atof(pos[0]);
	mrt->light.position.y = atof(pos[1]);
	mrt->light.position.z = atof(pos[2]);
	mrt->light.brightness = atof(tokens[2]);
	rgb = ft_split(tokens[3], ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		perror("Error: amb color");
		exit (1);
	}
	mrt->light.color.red = ft_atoi(rgb[0]);
	mrt->light.color.green = ft_atoi(rgb[1]);
	mrt->light.color.blue = ft_atoi(rgb[2]);
	free_array(pos);
	free_array(rgb);
}

void	parse_plane(char **tokens, t_mrt *mrt)
{
	char	**pos;
	char	**norm;
	char	**rgb;
	
	if(!tokens[1] || !tokens[2] || !tokens[3])
	{
		perror("Error: plane token");
		exit(1);
	}
	pos = ft_split(tokens[1], ',');
	if (!pos[0] || !pos[1] || !pos[2])
	{
		perror("Error: plane position");
		exit (1);
	}
	mrt->plane.position.x = atof(pos[0]);
	mrt->plane.position.y = atof(pos[1]);
	mrt->plane.position.z = atof(pos[2]);
	norm = ft_split(tokens[2], ',');
	if (!norm[0] || !norm[1] || !norm[2])
	{
		perror("Error: plane normal");
		exit (1);
	}
	mrt->plane.normal.x = atof(norm[0]);
	mrt->plane.normal.y = atof(norm[1]);
	mrt->plane.normal.z = atof(norm[2]);
	rgb = ft_split(tokens[3], ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		perror("Error: plane color");
		exit (1);
	}
	mrt->plane.color.red = ft_atoi(rgb[0]);
	mrt->plane.color.green = ft_atoi(rgb[1]);
	mrt->plane.color.blue = ft_atoi(rgb[2]);
	free_array(rgb);
	free_array(pos);
	free_array(norm);
}
void	parse_sphere(char **tokens, t_mrt *mrt)
{
	char	**pos;
	char	**rgb;
	
	if(!tokens[1] || !tokens[2] || !tokens[3])
	{
		perror("Error: sphere token");
		exit(1);
	}
	pos = ft_split(tokens[1], ',');
	if (!pos[0] || !pos[1] || !pos[2])
	{
		perror("Error: sphere position");
		exit (1);
	}
	mrt->sp.position.x = atof(pos[0]);
	mrt->sp.position.y = atof(pos[1]);
	mrt->sp.position.z = atof(pos[2]);
	mrt->sp.diameter = atof(tokens[2]);
	rgb = ft_split(tokens[3], ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		perror("Error: sphere color");
		exit (1);
	}
	mrt->sp.color.red = ft_atoi(rgb[0]);
	mrt->sp.color.green = ft_atoi(rgb[1]);
	mrt->sp.color.blue = ft_atoi(rgb[2]);
	free_array(rgb);
	free_array(pos);
}
void	parse_cylinder(char **tokens, t_mrt *mrt)
{
	char	**pos;
	char	**norm;
	char	**rgb;
	
	if(!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
	{
		perror("Error: cylinder token");
		exit(1);
	}
	pos = ft_split(tokens[1], ',');
	if (!pos[0] || !pos[1] || !pos[2])
	{
		perror("Error: cylinder position");
		exit (1);
	}
	mrt->cyl.position.x = atof(pos[0]);
	mrt->cyl.position.y = atof(pos[1]);
	mrt->cyl.position.z = atof(pos[2]);
	norm = ft_split(tokens[2], ',');
	if (!norm[0] || !norm[1] || !norm[2])
	{
		perror("Error: cylinder normal");
		exit (1);
	}
	mrt->cyl.normal.x = atof(norm[0]);
	mrt->cyl.normal.y = atof(norm[1]);
	mrt->cyl.normal.z = atof(norm[2]);
	mrt->sp.diameter = atof(tokens[3]);
	mrt->sp.diameter = atof(tokens[4]);
	rgb = ft_split(tokens[5], ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		perror("Error: cylinder color");
		exit (1);
	}
	mrt->cyl.color.red = ft_atoi(rgb[0]);
	mrt->cyl.color.green = ft_atoi(rgb[1]);
	mrt->cyl.color.blue = ft_atoi(rgb[2]);
	free_array(rgb);
	free_array(pos);
	free_array(norm);
}

void	parsing(char *filename, t_mrt *mrt)
{
	int				fd;
	char			*line;
	char			**tokens;

	fd = open(filename, O_RDONLY);
	if(fd < 0)
		return;
	// line = get_next_lin(fd);
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
		if (strcmp(tokens[0], "A") == 0)
			parse_ambient(tokens, mrt);
		if (strcmp(tokens[0], "C") == 0)
			parse_camera(tokens, mrt);
		if (strcmp(tokens[0], "L") == 0)
			parse_light(tokens, mrt);
		if (strcmp(tokens[0], "pl") == 0)
			parse_plane(tokens, mrt);
		if (strcmp(tokens[0], "sp") == 0)
			parse_sphere(tokens, mrt);
		if (strcmp(tokens[0], "cy") == 0)
			parse_cylinder(tokens, mrt);
		free_array(tokens);
		free(line);
	}
	close(fd);
}
