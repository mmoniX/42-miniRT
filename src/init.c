/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:17:50 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/10 17:49:37 by gahmed           ###   ########.fr       */
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
	//init_mrt (obj, light, HEIGHT, WIDTH, obj_count, light_count)
	map->mlx = mlx_init(WIDTH, HEIGHT, "miniRT: Ray Tracing Graphic", true);
	if (!map->mlx)
		return (free(map), NULL);
	map->image = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	if (!map->image)
	{
		printf("Failed to create image.\n");
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
	mrt->plane = (t_plane *)malloc(sizeof(t_plane) * MAX_SP);
	if (!mrt->plane)
	{
		ft_putstr_fd("Error: malloc failed for planes\n", STDERR_FILENO);
		exit(1);
	}
	mrt->sp_count = 0;
	mrt->sp = (t_sphere *)malloc(sizeof(t_sphere) * MAX_SP);
	if (!mrt->sp)
	{
		ft_putstr_fd("Error: malloc failed for spheres\n", STDERR_FILENO);
		exit(1);
	}
	mrt->cyl_count = 0;
	mrt->cyl = (t_cylinder *)malloc(sizeof(t_cylinder) * MAX_SP);
	if (!mrt->cyl)
	{
		ft_putstr_fd("Error: malloc failed for cylinder\n", STDERR_FILENO);
		exit(1);
	}
	mrt->cyl->height = 0.0f;
	mrt->cyl->diameter = 0.0f;
}
