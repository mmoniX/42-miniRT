/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:15:10 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/25 13:04:18 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/*
P = hit point which coming from P = origin + (t * direction)
C = sp_position;
N = (P - C) / abs(P - C)
*/
t_vector	hit_sphere(t_ray *ray, t_sphere *sp, double t)
{
	t_vector	p;
	t_vector	normal;

	p = v_add(ray->origin, v_m_sca(&ray->direction, t));
	normal = v_norm(v_sub(p, sp->position));
	return (normal);
}

int	sp_hit_info(t_ray *ray, t_sphere *sp, t_hit *hit)
{
	double	t;

	t = intersect_sphere(ray, sp);
	if (t > 0.001 && t < hit->distance)
	{
		hit->distance = t;
		hit->sp = sp;
		hit->pl = NULL;
		hit->cy = NULL;
		hit->ray = ray;
		hit->normal = hit_sphere(ray, sp, t);
		hit->position = v_add(ray->origin, v_m_sca(&ray->direction, t));
		hit->local_color = sp->color;
		return (TRUE);
	}
	return (FALSE);
}

// N = plane's normal
int	pl_hit_info(t_ray *ray, t_plane *pl, t_hit *hit)
{
	double	t;

	t = intersect_plane(ray, pl);
	if (t > 0.001 && t < hit->distance)
	{
		hit->distance = t;
		hit->pl = pl;
		hit->sp = NULL;
		hit->cy = NULL;
		hit->ray = ray;
		hit->normal = v_norm(pl->normal);
		if (v_dot(hit->normal, ray->direction) > 0)
			hit->normal = v_m_sca(&hit->normal, -1);
		hit->position = v_add(ray->origin, v_m_sca(&ray->direction, t));
		hit->local_color = pl->color;
		return (TRUE);
	}
	return (FALSE);
}

// N = {pc - (pc.n).n} / abs[{pc - (pc.n).n}]
t_vector	hit_cylinder(t_ray *ray, t_cylinder *cyl, double t)
{
	t_vector	point;
	t_vector	top;
	t_vector	bottom;
	t_vector	all;
	t_vector	proj;

	point = v_add(ray->origin, v_m_sca(&ray->direction, t));
	top = v_sub(point, cyl->cap1);
	if (fabs(v_dot(top, cyl->normal)) < 0.001
		&& v_length(top) <= cyl->diameter / 2 + 0.001)
		return (v_norm(cyl->normal));
	bottom = v_sub(point, cyl->cap2);
	if (fabs(v_dot(bottom, cyl->normal)) < 0.001
		&& v_length(bottom) <= cyl->diameter / 2 + 0.001)
		return (v_norm(v_m_sca(&cyl->normal, -1)));
	all = v_sub(point, cyl->position);
	proj = v_add(cyl->position, v_m_sca(&cyl->normal, v_dot(all, cyl->normal)));
	return (v_norm(v_sub(point, proj)));
}

int	cyl_hit_info(t_ray *ray, t_cylinder *cyl, t_hit *hit)
{
	double	t;

	t = intersect_cylinder(ray, cyl);
	if (t > 0.001 && t < hit->distance)
	{
		hit->distance = t;
		hit->cy = cyl;
		hit->sp = NULL;
		hit->pl = NULL;
		hit->ray = ray;
		hit->normal = hit_cylinder(ray, cyl, t);
		hit->position = v_add(ray->origin, v_m_sca(&ray->direction, t));
		hit->local_color = cyl->color;
		return (TRUE);
	}
	return (FALSE);
}
