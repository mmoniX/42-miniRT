/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:53:57 by mmonika           #+#    #+#             */
/*   Updated: 2025/05/27 13:19:24 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_col trace_ray(t_ray *ray, t_mrt *mrt)
{
	t_hit	hit;
	int		i;
	t_col final_color = (t_col){0, 0, 0};

	i = 0;
	hit.distance = INFINITY;
	mrt->is_sp = 0;
	mrt->is_pl = 0;
	mrt->hit = &hit;
	while (i < mrt->sp_count)
	{
		if (sp_hit_info(ray, &mrt->sp[i], &hit))
			mrt->is_sp = 1;
		i++;
	}
	i = 0;
	while (i < mrt->plane_count)
	{
		if (pl_hit_info(ray, &mrt->plane[i], &hit))
			mrt->is_pl = 1;
		i++;
	}
	i = 0;
	while (i < mrt->cyl_count)
	{
		if (cyl_hit_info(ray, &mrt->cyl[i], &hit))
			final_color = hit.local_color;
		i++;
	}
	i = 0;
	while (i < mrt->cyl_count)
	{
		if (cyl_hit_info(ray, &mrt->cyl[i], &hit))
			final_color = hit.local_color;
		i++;
	}
	if (hit.distance < INFINITY)
		final_color = calculate_light(mrt->hit, mrt);
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
P(t) = O + tD */

double intersect_sphere(t_ray *ray, t_sphere *sphere)
{
	double		a;
	double		b;
	double		c;
	t_vector	oc;
	double		discriminant;
	double		res1;
	double		res2;
	double		denom;

	oc = vector_subtraction(&ray->origin, &sphere->position);
	a = vector_dot(&ray->direction, &ray->direction);
	b = 2.0 * vector_dot(&oc, &ray->direction);
	c = vector_dot(&oc, &oc) - pow(sphere->diameter/2, 2);
	discriminant = b * b - 4 * a * c;
	if(discriminant < 0)
		return (-1.0);
	denom = 2.0 * a;
	res1 = (-b - sqrt(discriminant)) / denom;
	res2 = (-b + sqrt(discriminant)) / denom;
	if(res1 > 0.001)
		return( res1);
	if(res2 > 0.001)
		return( res2);
	return (-1.0);
}


/*
equations 
t = dot((PP - RO).PN)) / dot(Pn . RD);
*/

double	intersect_plane(t_ray *ray, t_plane *plane)
{
	double t;
	t_vector sub_po;
	double denom;

	denom = vector_dot(&plane->normal, &ray->direction);
	if(fabs(denom) < 1e-6)
		return (-1.0);
	sub_po = vector_subtraction(&plane->position, &ray->origin);
	t = vector_dot(&sub_po, &plane->normal) / denom;
	if (t > 0.001)
		return (t);
	return (-1.0);
}

t_quadratic solve_quadratic(double a, double b, double c)
{
	t_quadratic q;
	double discriminant;

	q.a = a;
	q.b = b;
	q.c = c;
	q.delta = b * b - 4 * a * c;
	q.t1 = -1;
	q.t2 = -1;

	if (q.delta < 0 || a == 0)
		return q;

	discriminant = sqrt(q.delta);
	q.t1 = (-b - discriminant) / (2 * a);
	q.t2 = (-b + discriminant) / (2 * a);
	return q;
}
