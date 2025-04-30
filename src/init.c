/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:17:50 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/30 17:14:33 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_map	*map_initialization(void)
{
	t_map	*map;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (free(map), NULL);
	map->width = 0;
	map->height = 0;
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

void init_mrt(t_mrt *mrt, t_col *col, t_vector *position)
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
	mrt->sp.diameter = 0.0f;
	mrt->cyl.height = 0.0f;
	mrt->cyl.diameter = 0.0f;
}