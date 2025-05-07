/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:53:57 by mmonika           #+#    #+#             */
/*   Updated: 2025/05/07 15:05:16 by gahmed           ###   ########.fr       */
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
	t_sphere *sphere = &mrt->sp; // or however you're storing it
	double t;
	if (intersect_sphere(ray, sphere, &t))
	{
		printf("Hit sphere at t=%f\n", t);
		return sphere->color;
	}
	return (t_col){128, 128, 128}; // Background color
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

// int intersect_sphere(t_ray *ray, t_sphere *sphere, double *t_out)
// {
// 	t_vector oc = vector_subtraction(&ray->origin, &sphere->position);
// 	double a = vector_dot(&ray->direction, &ray->direction);
// 	double b = 2.0 * vector_dot(&oc, &ray->direction);
// 	double c = vector_dot(&oc, &oc) - (sphere->diameter / 2.0) * (sphere->diameter / 2.0);
// 	double discriminant = b * b - 4 * a * c;

// 	if (discriminant < 0)
// 		return false;

// 	double sqrt_disc = sqrt(discriminant);
// 	double t1 = (-b - sqrt_disc) / (2.0 * a);
// 	double t2 = (-b + sqrt_disc) / (2.0 * a);

// 	if (t1 > 0.001) {
// 		*t_out = t1;
// 		return TRUE;
// 	}
// 	if (t2 > 0.001) {
// 		*t_out = t2;
// 		return TRUE;
// 	}
// 	return FALSE;
// }
