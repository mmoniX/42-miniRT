/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:56:55 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/29 18:51:04 by gahmed           ###   ########.fr       */
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
	// free_array(rgb); //free array
}

void	parsing(char *filename, t_mrt *mrt)
{
	int				fd;
	char			*line;
	char			**column;
	char			**tokens;

	fd = open(filename, O_RDONLY);
	if(fd < 0)
		return;
	// line = get_next_lin(fd);
	while (line = get_next_lin(fd))
	{
		if(*line == '\0')
		{
			free(line);
			continue;
		}
		tokens = ft_split(line, ' ');
		if (!tokens || !tokens[0])
		{
			free(line);
			continue;
		}
		if (strcmp(tokens[0], "A") == 0)
			parse_ambient(tokens, mrt);
	}
	free(line);
	close(fd);
}
