/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:46:53 by gahmed            #+#    #+#             */
/*   Updated: 2025/06/11 13:16:17 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

double	cy_cap_hit(t_ray *ray, t_vector cap_cen, t_vector cap_norm, double rad)
{
	double		denom;
	double		t;
	t_vector	p;
	t_vector	to_cap;
	t_vector	temp_vec;

	denom = v_dot(ray->direction, cap_norm);
	if (fabs(denom) > 1e-6)
	{
		to_cap = v_sub(cap_cen, ray->origin);
		t = v_dot(to_cap, cap_norm) / denom;
		if (t < 0)
			return (-1.0);
		temp_vec = v_m_sca(&ray->direction, t);
		p = v_add(ray->origin, temp_vec);
		if (v_mag(&p, &cap_cen) <= rad)
			return (t);
	}
	return (-1.0);
}

void	cylinder_caps_hit(t_ray	*ray, t_cylinder *cyl, double *t_min)
{
	double	t_cap;

	t_cap = cy_cap_hit(ray, cyl->cap1, cyl->normal, cyl->diameter / 2);
	if (t_cap >= 0 && t_cap < *t_min)
		*t_min = t_cap;
	t_cap = cy_cap_hit(ray, cyl->cap2, cyl->normal, cyl->diameter / 2);
	if (t_cap >= 0 && t_cap < *t_min)
		*t_min = t_cap;
}

/* 
equations
p(t) = O + t * D
(x - a)² + y² = r₂² 
x² - 2 * x * a + a² + y² = r²
*/
t_quadratic	cyl_eq(t_ray *ray, t_cylinder *cyl)
{
	t_quadratic	q;
	t_vector	oc;
	double		dir_dot_n;
	double		oc_dot_n;
	double		radius;

	radius = cyl->diameter / 2.0;
	oc = v_sub(ray->origin, cyl->position);
	dir_dot_n = v_dot(ray->direction, cyl->normal);
	oc_dot_n = v_dot(oc, cyl->normal);
	q.a = v_dot(ray->direction, ray->direction) - dir_dot_n * dir_dot_n;
	q.b = 2.0 * (v_dot(ray->direction, oc) - dir_dot_n * oc_dot_n);
	q.c = v_dot(oc, oc) - oc_dot_n * oc_dot_n - radius * radius;
	q = solve_quadratic(q.a, q.b, q.c);
	return (q);
}

double	intersect_cylinder(t_ray *ray, t_cylinder *cyl)
{
	t_quadratic	q;
	double		t_min;
	int			i;
	double		ts[2];

	t_min = INFINITY;
	q = cyl_eq(ray, cyl);
	if (q.delta < 0)
		return (-1.0);
	ts[0] = q.t1;
	ts[1] = q.t2;
	i = 0;
	while (i < 2 && ts[i] >= 0)
	{
		if (v_dot(v_sub(v_add(ray->origin, v_m_sca(&ray->direction, ts[i])),
					cyl->cap1), cyl->normal) * v_dot(v_sub(v_add(ray->origin,
						v_m_sca(&ray->direction, ts[i])), cyl->cap2),
				cyl->normal) <= 0.0)
			t_min = fmin(t_min, ts[i]);
		i++;
	}
	cylinder_caps_hit(ray, cyl, &t_min);
	if (t_min < INFINITY)
		return (t_min);
	return (-1.0);
}
