/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:56:55 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/09 17:10:52 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parse_plane(char **tokens, t_mrt *mrt)
{
	t_plane	*plane;

	if (mrt->plane_count >= MAX_SP)
	{
		ft_putstr_fd("Error: too many planes\n", STDERR_FILENO);
		exit(1);
	}
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		ft_putstr_fd("Error: plane token", STDERR_FILENO);
		exit(1);
	}
	plane = &mrt->plane[mrt->plane_count];
	plane->position = parse_point(tokens[1]);
	plane->normal = parse_point(tokens[2]);
	if (!is_valid_normal(plane->normal, -1, 1))
	{
		ft_putstr_fd("Error: plane Norm out of range", STDERR_FILENO);
		exit(1);
	}
	plane->color = parse_color(tokens[3]);
	mrt->plane_count++;
}

void	parse_sphere(char **tokens, t_mrt *mrt)
{
	t_sphere	*sphere;

	if (mrt->sp_count >= MAX_SP)
	{
		ft_putstr_fd("Error: too many spheres\n", STDERR_FILENO);
		exit(1);
	}
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		ft_putstr_fd("Error: sphere token", STDERR_FILENO);
		exit(1);
	}
	sphere = &mrt->sp[mrt->sp_count];
	sphere->position = parse_point(tokens[1]);
	sphere->diameter = ft_atof(tokens[2]);
	sphere->color = parse_color(tokens[3]);
	mrt->sp_count++;
}

void	parse_cylinder(char **tokens, t_mrt *mrt)
{
	t_cylinder	*cyl;
	t_vector	half_height;

	if (mrt->cyl_count >= MAX_SP)
	{
		ft_putstr_fd("Error: too many cylinder\n", STDERR_FILENO);
		exit(1);
	}
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
	{
		ft_putstr_fd("Error: cylinder token", STDERR_FILENO);
		exit(1);
	}
	cyl = &mrt->cyl[mrt->cyl_count];
	cyl->position = parse_point(tokens[1]);
	cyl->normal = vector_normalization(parse_point(tokens[2]));
	if (!is_valid_normal(cyl->normal, -1, 1))
	{
		ft_putstr_fd("Error: cylinder Norm out of range", STDERR_FILENO);
		exit(1);
	}
	cyl->diameter = ft_atof(tokens[3]);
	cyl->height = ft_atof(tokens[4]);
	cyl->color = parse_color(tokens[5]);
	half_height = vector_mult_scalar(&cyl->normal, cyl->height / 2.0);
	cyl->cap1 = vector_subtraction(&cyl->position, &half_height);
	cyl->cap2 = vector_addition(&cyl->position, &half_height);
	mrt->cyl_count++;
}
