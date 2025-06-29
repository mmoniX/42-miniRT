/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:52:15 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/25 12:18:42 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//radius = 0.2;
t_vector	random_light(t_light *light)
{
	double	theta;
	double	phi;
	double	x;
	double	y;
	double	z;

	theta = ((double)rand() / RAND_MAX) * 2.0 * M_PI;
	phi = acos(2.0 * ((double)rand() / RAND_MAX) - 1.0);
	x = 0.2 * sin(phi) * cos(theta);
	y = 0.2 * sin(phi) * sin(theta);
	z = 0.2 * cos(phi);
	return (v_add(light->position, (t_vector){x, y, z}));
}

int	ft_soft_shadow(t_hit *hit, t_mrt *mrt, int samples)
{
	int			i;
	int			blocked_ray;
	t_ray		shadow_ray;
	t_hit		tmp_hit;
	t_vector	direction;

	i = 0;
	blocked_ray = 0;
	while (i < samples)
	{
		direction = v_sub(random_light(&mrt->light), hit->position);
		shadow_ray.origin = v_add(hit->position, v_m_sca(&hit->normal, 0.001));
		shadow_ray.direction = v_norm(direction);
		shadow_ray.depth = 0;
		tmp_hit.distance = INFINITY;
		obj_intersect(&shadow_ray, mrt, &tmp_hit);
		if (tmp_hit.distance < v_length(direction) - 0.001)
			blocked_ray++;
		i++;
	}
	return (blocked_ray / (double) samples);
}
