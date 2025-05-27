/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:46:53 by gahmed            #+#    #+#             */
/*   Updated: 2025/05/27 12:56:23 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

double	cylinder_cap_hit(t_ray *ray, t_vector cap_center, t_vector cap_normal, double radius)
{
	double		denom;
	double		t;
	t_vector	p;
	t_vector	to_cap;

	denom = vector_dot(&ray->direction, &cap_normal);
	if (fabs(denom) > 1e-6)
	{
		to_cap = vector_subtraction(&cap_center, &ray->origin);
		t = vector_dot(&to_cap, &cap_normal) / denom;
		if (t < 0)
			return (-1.0);
		t_vector temp_vec = vector_multiplication(&ray->direction, t);
		p = vector_addition(&ray->origin, &temp_vec);
		if (vector_magnitude(&p, &cap_center) <= radius)
			return (t);
	}
	return (-1.0);
}


void	cylinder_caps_hit(t_ray	*ray, t_cylinder *cyl, double *t_min)
{
	double	t_cap;

	t_cap = cylinder_cap_hit(ray, cyl->cap1, cyl->normal, cyl->diameter/2);
	if (t_cap >= 0 && t_cap < *t_min)
		*t_min = t_cap;
	t_cap = cylinder_cap_hit(ray, cyl->cap2, cyl->normal, cyl->diameter/2);
	if (t_cap >= 0 && t_cap < *t_min)
		*t_min = t_cap;
}

/* 
equations
p(t) = O + t * D
(x - a)² + y² = r₂² 
x² - 2 * x * a + a² + y² = r²
*/
t_quadratic cyl_eq(t_ray *ray, t_cylinder *cyl)
{
	t_quadratic	q;
	t_vector	oc;
	double		dir_dot_n;
	double		oc_dot_n;
	double		radius;
	
	radius = cyl->diameter / 2.0;
	oc = vector_subtraction(&ray->origin, &cyl->position);
	dir_dot_n = vector_dot(&ray->direction, &cyl->normal);
	oc_dot_n = vector_dot(&oc, &cyl->normal);

	q.a = vector_dot(&ray->direction, &ray->direction) - dir_dot_n * dir_dot_n;
	q.b = 2.0 * (vector_dot(&ray->direction, &oc) - dir_dot_n * oc_dot_n);
	q.c = vector_dot(&oc, &oc) - oc_dot_n * oc_dot_n - radius * radius;

	q = solve_quadratic(q.a, q.b, q.c);
	return q;
}

double intersect_cylinder(t_ray *ray, t_cylinder *cyl)
{
	t_quadratic	q;
	t_vector	p;
	t_vector	v1, v2;
	double		t_min = INFINITY;
	double		t;
	int			i;

	q = cyl_eq(ray, cyl);
	if (q.delta < 0)
		return -1.0;

	double ts[2] = { q.t1, q.t2 };
	for (i = 0; i < 2; i++)
	{
		t = ts[i];
		if (t < 0.001) continue;

		t_vector temp_vec = vector_multiplication(&ray->direction, t);
		p = vector_addition(&ray->origin, &temp_vec);
		v1 = vector_subtraction(&p, &cyl->cap1);
		v2 = vector_subtraction(&p, &cyl->cap2);

		// inside the height bounds
		if (vector_dot(&v1, &cyl->normal) * vector_dot(&v2, &cyl->normal) <= 0.0)
			if (t < t_min) t_min = t;
	}

	// check caps
	cylinder_caps_hit(ray, cyl, &t_min);
	if (t_min < INFINITY)
		return t_min;

	return -1.0;
}

