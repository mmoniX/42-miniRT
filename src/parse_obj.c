/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:56:55 by mmonika           #+#    #+#             */
/*   Updated: 2025/05/04 15:37:14 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parse_plane(char **tokens, t_mrt *mrt)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		ft_putstr_fd("Error: plane token", STDERR_FILENO);
		exit(1);
	}
	mrt->plane.position = parse_point(tokens[1]);
	mrt->plane.normal = parse_point(tokens[2]);
	if (!is_valid_normal(mrt->plane.normal, -1, 1))
	{
		ft_putstr_fd("Error: plane Norm out of range", STDERR_FILENO);
		exit(1);
	}
	mrt->plane.color = parse_color(tokens[3]);
}

void	parse_sphere(char **tokens, t_mrt *mrt)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		ft_putstr_fd("Error: sphere token", STDERR_FILENO);
		exit(1);
	}
	mrt->sp.position = parse_point(tokens[1]);
	mrt->sp.diameter = ft_atof(tokens[2]);
	mrt->sp.color = parse_color(tokens[3]);
}

void	parse_cylinder(char **tokens, t_mrt *mrt)
{
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
	{
		ft_putstr_fd("Error: cylinder token", STDERR_FILENO);
		exit(1);
	}
	mrt->cyl.position = parse_point(tokens[1]);
	mrt->cyl.normal = parse_point(tokens[2]);
	if (!is_valid_normal(mrt->cyl.normal, -1, 1))
	{
		ft_putstr_fd("Error: cylinder Norm out of range", STDERR_FILENO);
		exit(1);
	}
	mrt->cyl.diameter = ft_atof(tokens[3]);
	mrt->cyl.height = ft_atof(tokens[4]);
	mrt->cyl.color = parse_color(tokens[5]);
}
