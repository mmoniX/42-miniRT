/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:53:57 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/14 17:45:26 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_col	trace_ray(t_ray *ray, t_mrt *mrt)
{
	t_hit	hit;
	t_ray	ref_ray;
	t_col	ref_col;
	t_col	final_color;

	final_color = (t_col){0, 0, 0};
	hit.distance = INFINITY;
	mrt->hit = &hit;
	obj_intersect(ray, mrt, &hit);
	if (hit.distance < INFINITY)
	{
		final_color = calculate_light(mrt->hit, mrt);
		if (hit.reflect > 0 && ray->depth < 5)
		{
			compute_ref(&hit, &ref_ray);
			ref_ray.depth = ray->depth + 1;
			ref_col = trace_ray(&ref_ray, mrt);
			final_color = c_add(final_color, c_m_sca(ref_col, hit.reflect));
		}
	}
	return (final_color);
}

/*
equations 
a.t^2 + 2bt + c
t = (-b +/- sqrt(b^2 - 4ac)) / 2a
a = D.D
b = (O - C).D
c = (O - C).(O - C) - r^2
||P(t) - C||^2 = r^2
P(t) = O + tD 
*/
double	intersect_sphere(t_ray *ray, t_sphere *sphere)
{
	t_quadratic	q;
	t_vector	oc;

	oc = v_sub(ray->origin, sphere->position);
	q.a = v_dot(ray->direction, ray->direction);
	q.b = 2.0 * v_dot(oc, ray->direction);
	q.c = v_dot(oc, oc) - pow(sphere->diameter / 2, 2);
	q = solve_quadratic(q.a, q.b, q.c);
	if (q.t1 > 0.001)
		return (q.t1);
	if (q.t2 > 0.001)
		return (q.t2);
	return (-1.0);
}

/*
equations 
t = dot((PP - RO).PN)) / dot(Pn . RD);
*/
double	intersect_plane(t_ray *ray, t_plane *plane)
{
	double		t;
	t_vector	sub_po;
	double		denom;

	denom = v_dot(plane->normal, ray->direction);
	if (fabs(denom) < 1e-6)
		return (-1.0);
	sub_po = v_sub(plane->position, ray->origin);
	t = v_dot(sub_po, plane->normal) / denom;
	if (t > 0.001)
		return (t);
	return (-1.0);
}

t_quadratic	solve_quadratic(double a, double b, double c)
{
	t_quadratic	q;
	double		discriminant;

	q.a = a;
	q.b = b;
	q.c = c;
	q.delta = b * b - 4 * a * c;
	q.t1 = -1;
	q.t2 = -1;
	if (q.delta < 0 || a == 0)
		return (q);
	discriminant = sqrt(q.delta);
	q.t1 = (-b - discriminant) / (2 * a);
	q.t2 = (-b + discriminant) / (2 * a);
	return (q);
}

void	obj_intersect(t_ray *ray, t_mrt *mrt, t_hit *hit)
{
	int		i;

	i = -1;
	while (++i < mrt->sp_count)
		sp_hit_info(ray, &mrt->sp[i], hit);
	i = -1;
	while (++i < mrt->plane_count)
		pl_hit_info(ray, &mrt->plane[i], hit);
	i = -1;
	while (++i < mrt->cyl_count)
		cyl_hit_info(ray, &mrt->cyl[i], hit);
}
