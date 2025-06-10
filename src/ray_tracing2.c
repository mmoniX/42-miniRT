/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:15:10 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/10 14:32:52 by mmonika          ###   ########.fr       */
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

	dt = v_m_sca(&ray->direction, t);
	p = v_add(ray->origin, dt);
	diff = (t_vector){p.x - sp->diameter / 2.0, p.y - sp->diameter / 2.0, p.z - sp->diameter / 2.0};
	normal = v_norm(diff); 
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
		dt = v_m_sca(&ray->direction, t);
		hit->position = v_add(ray->origin, dt);
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
		hit->normal = v_norm(pl->normal);
		dt = v_m_sca(&ray->direction, t);
		hit->position = v_add(ray->origin, dt);
		hit->local_color = pl->color;
		return (TRUE);
	}
	return (FALSE);
}

/* 
N = {pc - (pc.n).n} / abs[{pc - (pc.n).n}]
*/

t_vector hit_cylinder(t_ray *ray, t_cylinder *cyl, double t)
{
	t_vector	point;    // intersection point
	t_vector	v;        // vector from cylinder center to point
	t_vector	projected;
	t_vector	normal;
	t_vector	temp_vector;

	temp_vector = v_m_sca(&ray->direction, t);
	point = v_add(ray->origin, temp_vector);
	v = v_sub(point, cyl->position);
	projected = v_m_sca(&cyl->normal, v_dot(&v, &cyl->normal));
	normal = v_norm(v_sub(v, projected));
	return normal;
}

int	cyl_hit_info(t_ray *ray, t_cylinder *cyl, t_hit *hit)
{
	double	t;
	t_vector	dt;

	t = intersect_cylinder(ray, cyl);
	if (t > 0.001)
	{
		hit->distance = t;
		hit->cy = cyl;
		hit->ray = ray;
		hit->normal = hit_cylinder(ray, cyl, t);
		dt = v_m_sca(&ray->direction, t);
		hit->position = v_add(ray->origin, dt);
		hit->local_color = cyl->color;
		return (TRUE);
	}
	return (FALSE);
}
