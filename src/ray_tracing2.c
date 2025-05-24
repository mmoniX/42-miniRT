/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:15:10 by mmonika           #+#    #+#             */
/*   Updated: 2025/05/24 17:08:22 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// p = hit point which coming from P = origin + (t * direction)
// c = center of sp (i.e. diameter / 2);
// N = (P - C) / abs(P - C)

t_vector	hit_sphere(t_ray *ray, t_sphere *sp, double t)
{
	t_vector	dt;
	t_vector	p;
	t_vector	diff;
	t_vector	normal;

	dt = vector_mult_scalar(&ray->direction, t);
	p = vector_addition(&ray->origin, &dt);
	diff = (t_vector){p.x - sp->diameter / 2.0, p.y - sp->diameter / 2.0, p.z - sp->diameter / 2.0};
	normal = vector_normalization(&diff); 
	return (normal);
}	

int	sp_hit_info(t_ray *ray, t_sphere *sp, t_hit *hit)
{
	double	t;
	t_vector	dt;

	t = intersect_sphere(ray, sp);
	if (t > 0.001)
	{
		hit->distance = t;
		hit->sp = sp;
		hit->ray = ray;
		hit->normal = hit_sphere(ray, sp, t);
		dt = vector_mult_scalar(&ray->direction, t);
		hit->position = vector_addition(&ray->origin, &dt);
		hit->local_color = sp->color;
		return (TRUE);
	}
	return (FALSE);
}

// N = plane's normal

int	pl_hit_info(t_ray *ray, t_plane *pl, t_hit *hit)
{
	double	t;
	t_vector	dt;

	t = intersect_plane(ray, pl);
	if (t > 0.001 && t < hit->distance)
	{
		hit->distance = t;
		hit->pl = pl;
		hit->ray = ray;
		hit->normal = vector_normalization(&pl->normal);
		dt = vector_mult_scalar(&ray->direction, t);
		hit->position = vector_addition(&ray->origin, &dt);
		hit->local_color = pl->color;
		return (TRUE);
	}
	return (FALSE);
}
