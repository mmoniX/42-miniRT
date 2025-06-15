/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:43:32 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/15 13:30:59 by mmonika          ###   ########.fr       */
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

//v_w = v0, v_h = v1 for horizontal FOV
void	set_background(t_mrt *mrt, double *v0, double *v1)
{
	double	theta;
	double	a_ratio;

	theta = mrt->camera.fov * (M_PI / 180);
	a_ratio = WIDTH / HEIGHT;
	*v0 = 2.0 * tan(theta / 2);
	*v1 = *v0 / a_ratio;
}

/*
s_x = slop[0], s_y = slop[1]
v_m_sca(&R, s_x) store as Horizontal_Vector (H)
v_m_sca(&U, s_y) store as Vertical_Vector (V = &U, v_h)
res store as (LL = origin-0.5H-0.5v+F)
*/
t_vector	ray_res(t_mrt *mrt, double u, double v, t_vector uu_w)
{
	t_vector	res;
	t_vector	r;
	t_vector	uu;
	double		slop[2];
	double		hv[2];

	r = v_norm(v_cross(&mrt->camera.normal, &uu_w));
	uu = v_norm(v_cross(&r, &mrt->camera.normal));
	set_background(mrt, &hv[0], &hv[1]);
	slop[0] = (2 * u - 1) * (hv[0] / 2);
	slop[1] = (1 - 2 * v) * (hv[1] / 2);
	res = v_add(v_add(v_m_sca(&r, slop[0]),
				v_m_sca(&uu, slop[1])), mrt->camera.normal);
	return (res);
}

t_ray	generate_ray(t_mrt *mrt, int x, int y)
{
	double		u;
	double		v;
	t_vector	uu_w;
	t_vector	res;
	t_ray		ray;

	if (mrt->camera.normal.x == 0 && mrt->camera.normal.y == 0
		&& mrt->camera.normal.z == 0)
	{
		ft_putstr_fd("camera.normal null. Using {0, 0, -1}.\n", STDERR_FILENO);
		mrt->camera.normal.z = -1;
	}
	u = (x + 0.5) / WIDTH;
	v = (y + 0.5) / HEIGHT;
	if (fabs(mrt->camera.normal.y) == 1.0)
		uu_w = (t_vector){0.0, 0.0, 1};
	else
		uu_w = (t_vector){0.0, 1.0, 0.0};
	res = ray_res(mrt, u, v, uu_w);
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