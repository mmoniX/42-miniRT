/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:17:50 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/21 18:21:45 by mmonika          ###   ########.fr       */
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
	map->mlx = mlx_init(WIDTH, HEIGHT, "miniRT: minimal Ray Tracing Graphic", true);
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
