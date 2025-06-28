/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:17:50 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/28 19:38:36 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_map	*map_initialization(void)
{
	t_map	*map;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (free(map), NULL);
	map->width = WIDTH;
	map->height = HEIGHT;
	map->mlx = mlx_init(WIDTH, HEIGHT, "miniRT: Ray Tracing Graphic", true);
	if (!map->mlx)
		return (free(map), NULL);
	map->image = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	if (!map->image)
	{
		ft_putstr_fd("Error\nFailed to create image.\n", STDERR_FILENO);
		return (free(map), NULL);
	}
	return (map);
}

void	init_mrt(t_mrt *mrt, t_col *col, t_vector *position)
{
	col->red = 255;
	col->green = 255;
	col->blue = 255;
	position->x = 0.0;
	position->y = 0.0;
	position->z = 0.0;
	mrt->amb.ratio = 0.0f;
	mrt->camera.fov = 0.0;
	mrt->light.brightness = 0.0f;
	mrt->plane_count = 0;
	mrt->plane = (t_plane *)malloc(sizeof(t_plane) * SIZE);
	if (!mrt->plane)
		return (free(mrt->plane),
			ft_putstr_fd("Error\nPlane: malloc failed\n", STDERR_FILENO));
	mrt->sp_count = 0;
	mrt->sp = (t_sphere *)malloc(sizeof(t_sphere) * SIZE);
	if (!mrt->sp)
		return (free(mrt->sp), ft_putstr_fd("Error\nSp malloc\n", 2));
	mrt->cyl_count = 0;
	mrt->cyl = (t_cylinder *)malloc(sizeof(t_cylinder) * SIZE);
	if (!mrt->cyl)
		return (free(mrt->cyl),
			ft_putstr_fd("Error\nCylinder: malloc failed\n", STDERR_FILENO));
	mrt->cyl->height = 0.0f;
	mrt->cyl->diameter = 0.0f;
}
