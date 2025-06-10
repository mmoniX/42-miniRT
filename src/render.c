/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:43:32 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/10 14:34:25 by mmonika          ###   ########.fr       */
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

t_ray	generate_ray(t_mrt *mrt, int x, int y)
{
	double	theta;
	double	a_ratio;
	double	v_w;
	double	v_h;
	t_vector	U_w;
	t_vector	R;
	t_vector	U;
	double		u;
	double		v;
	double		s_x;
	double		s_y;
	t_vector	res;
	t_ray		ray;

	if (mrt->camera.normal.x == 0 && mrt->camera.normal.y == 0 && mrt->camera.normal.z == 0)
    {
        ft_putstr_fd("camera.normal is a zero vector. Using default {0, 0, 1}.\n", STDERR_FILENO);
        mrt->camera.normal = (t_vector){0, 0, 1};
    }
	theta = mrt->camera.fov * (M_PI / 180);
	a_ratio = WIDTH / HEIGHT;
	v_w = 2.0 * tan(theta / 2);					//for horizontal FOV
	v_h = v_w / a_ratio;						//for horizontal FOV
	if (fabs(mrt->camera.normal.y) == 1.0)
		U_w = (t_vector){0.0, 0.0, 1};
	else
		U_w = (t_vector){0.0, 1.0, 0.0};
	R = v_norm(v_cross(&mrt->camera.normal, &U_w));
	U = v_norm(v_cross(&R, &mrt->camera.normal));
	u = (x + 0.5) / WIDTH;
	v = (y + 0.5) / HEIGHT;
	s_x = (2 * u - 1) * (v_w / 2);
	s_y = (1 - 2 * v) * (v_h / 2);
	t_vector temp1 = v_m_sca(&R, s_x); //store as Horizontal_Vector (H)
	t_vector temp2 = v_m_sca(&U, s_y); //store as Vertical_Vector (V = &U, v_h)
	res = v_add(v_add(temp1, temp2), mrt->camera.normal); //store as (LL = origin-0.5H-0.5v+F)
	ray.direction = v_norm(res);
	ray.origin = mrt->camera.position;
	ray.depth = 0;	
	return (ray);
}

void	rendering(t_map *map, t_mrt *mrt)
{
	unsigned int	i;
	unsigned int	j;
	t_ray			ray;
	t_col			ray_color;

	clear_background(map->image);
	i = -1;
	while (++i < map->width)
	{
		j = -1;
		while (++j < map->height)
		{
			ray = generate_ray(mrt, i, j);
			ray_color = clamp_color(trace_ray(&ray, mrt));
			mlx_put_pixel(map->image, i, j, rgba_channel(ray_color));
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