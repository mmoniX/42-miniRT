/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:43:32 by mmonika           #+#    #+#             */
/*   Updated: 2025/05/06 17:36:39 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	clear_background(mlx_image_t *image)
{
	int	i;
	int	total_pixel;

	i = 0;
	total_pixel = image->height * image->width;
	while (i < total_pixel)
	{
		image->pixels[i] = 0;
		i++;
	}
}

void	viewing_position()

t_ray	generate_ray(t_mrt *mrt, )

void	rendering(t_map *map)
{
	unsigned int	i;
	unsigned int	j;

	clear_background(map->image);
	i = -1;
	while (++i < map->width)
	{
		j = -1;
		while (++j < map->height)
		{
			// ray = generate_ray();
			// ray_color = trace_ray(ray, );
			mlx_put_pixel(map->image, i, j, //ray_color());
		}
	}
	mlx_image_to_window(map->mlx, map->image, 0, 0);
}

// render()
//     for each pixel (x, y) in the image:
//         ray = generate_ray(x, y, camera)
//         color = trace_ray(ray, depth=0)
//         set_pixel(x, y, color)
//     save_image_to_file()