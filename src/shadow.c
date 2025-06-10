/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:52:15 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/10 15:48:08 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	random_light(t_light *light)
{
	double	radius;
	double	theta;
	double	phi;
	double	x;
	double	y;
	double	z;

	radius = 0.2;
	theta = ((double)rand() / RAND_MAX) * 2.0 * M_PI;
	phi = acos(2.0 * ((double)rand() / RAND_MAX) - 1.0);
	x = radius * sin(phi) * cos(theta);
	y = radius * sin(phi) * sin(theta);
	z = radius * cos(phi);
    return (v_add(light->position, (t_vector){x, y, z}));
}

static int is_blocked(t_ray *ray, t_mrt *mrt, t_hit *shadow_hit)
{
    int i;
	int obj;
	int block;

    i = 0;
	block = 0;
	obj = mrt->cyl_count + mrt->plane_count + mrt->sp_count; //
	while (i < obj)
	{
		if (sp_hit_info(ray, &mrt->sp[i], shadow_hit) && shadow_hit->distance < ray->depth)
		{
			block = 1;
			break ;
		}
		if (pl_hit_info(ray, &mrt->plane[i], shadow_hit) && shadow_hit->distance < ray->depth)
		{
			block = 1;
			break ;
		}
		if (cyl_hit_info(ray, &mrt->cyl[i], shadow_hit) && shadow_hit->distance < ray->depth)
		{
			block = 1;
			break ;
		}
		i++;
	}
    return block;
}

int ft_soft_shadow(t_hit *hit, t_mrt *mrt, int samples)
{
    int     i, occluded = 0;
    t_ray   shadow_ray;
    t_hit   tmp_hit;
    double  bias = 0.001;

    for (i = 0; i < samples; i++)
    {
        t_vector direction = v_norm(v_sub(random_light(&mrt->light), hit->position));
        double distance_to_light = sqrt(pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2));
        shadow_ray.origin = v_add(hit->position, v_m_sca(&hit->normal, bias));
        shadow_ray.direction = direction;
        // shadow_ray.depth = 0;
        tmp_hit.distance = distance_to_light;
		if (is_blocked(&shadow_ray, mrt, &tmp_hit))
            occluded++;
    }
    return (samples - occluded) / (double) samples;
}
