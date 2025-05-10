/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:53:57 by mmonika           #+#    #+#             */
/*   Updated: 2025/05/10 17:08:30 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/* t_col	trace_ray(t_ray *ray,t_mrt *mrt)
{
	    // Step 1: Initialize closest intersection tracking
		double closest_t = INFINITY;
		t_col final_color = {0, 0, 0};  // Default: background color (black)
	
		// Step 2: Intersect with each object in the scene
	
		// -- Sphere
		double t_sphere = intersect_sphere(ray, &mrt->sp);
		if (t_sphere > 0 && t_sphere < closest_t)
		{
			closest_t = t_sphere;
			final_color = mrt->sp.color;
		}
	
		// // -- Plane
		// double t_plane = intersect_plane(ray, mrt->plane);
		// if (t_plane > 0 && t_plane < closest_t)
		// {
		// 	closest_t = t_plane;
		// 	final_color = mrt->plane.color;
		// }
	
		// // -- Cylinder
		// double t_cyl = intersect_cylinder(ray, mrt->cyl);
		// if (t_cyl > 0 && t_cyl < closest_t)
		// {
		// 	closest_t = t_cyl;
		// 	final_color = mrt->cyl.color;
		// }
	
		// Step 3: Return the final color
		return final_color;
} */

t_col trace_ray(t_ray *ray, t_mrt *mrt)
{
	double	closest_t = INFINITY;
	double t;
	int i;
	t_col color = {128, 128, 128};
	
	i = 0;
	while (i < mrt->sp_count)
	{
		if (intersect_sphere(ray, &mrt->sp[i], &t))
		{
			if(t < closest_t)
			{
				closest_t = t;
				color = mrt->sp[i].color;
			}
		}
		i++;
	}
	i = 0;
	while (i < mrt->plane_count)
	{
		if (intersect_plane(ray, &mrt->plane[i], &t))
		{
			if(t < closest_t)
			{
				closest_t = t;
				color = mrt->plane[i].color;
			}
		}
		i++;
	}
	return (color);
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

int intersect_sphere(t_ray *ray, t_sphere *sphere, double *t_hit)
{
	double		a;
	double		b;
	double		c;
	t_vector	oc;
	double		discriminant;
	double		res1;
	double		res2;

	oc = vector_subtraction(&ray->origin, &sphere->position);
	a = vector_dot(&ray->direction, &ray->direction);
	b = 2.0 * vector_dot(&oc, &ray->direction);
	c = vector_dot(&oc, &oc) - pow(sphere->diameter/2, 2);
	discriminant = b * b - 4 * a * c;
	if(discriminant < 0)
		return (FALSE);
	res1 = (-b - sqrt(discriminant)) / (2.0 * a);
	res2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if(res1 > 0.001)
	{
		*t_hit = res1;
		return(TRUE);
	}
	if(res2 > 0.001)
	{
		*t_hit = res2;
		return(TRUE);
	}
	return (FALSE);
}

/*
equations 
t = dot((PP - RO).PN)) / dot(Pn . RD);

*/

int intersect_plane(t_ray *ray, t_plane *plane, double *t_hit)
{
	double t;
	t_vector sub_po;
	double denom;

	denom = vector_dot(&plane->normal, &ray->direction);
	if(fabs(denom) < 1e-6)
	{
		return (FALSE);
	}
	sub_po = vector_subtraction(&plane->position, &ray->origin);
	t = vector_dot(&sub_po, &plane->normal) / denom;
	if (t > 0.001)
	{
		*t_hit = t;
		return (TRUE);
	}
	return (FALSE);
}


