/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:02:46 by mmonika           #+#    #+#             */
/*   Updated: 2025/05/24 17:21:39 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_col	calculate_light(t_hit *hit, t_mrt *mrt)
{
	t_col	final_color;
	t_col	ambient_light;
	t_col	diffuse_light;
	// t_col	specular_light;
	// t_col	reflection_light;
	// t_col	phong_light (!shadow -> diffuse // reflection // !shadow -> specular)

	ambient_light = compute_ambient_light(hit, &mrt->amb);
	diffuse_light = compute_diffuse_light(hit, &mrt->light);
	final_color = color_add(&ambient_light, &diffuse_light);
	return (final_color);
}

//L_ambient = C_object * C_ambient_light * I_ambient
t_col	compute_ambient_light(t_hit *hit, t_amb *amb)
{
	t_col	ambcol;

	ambcol = color_mult(hit->local_color, amb->color);
	ambcol.red *= amb->ratio;
	ambcol.green *= amb->ratio;
	ambcol.blue *= amb->ratio;
	return (ambcol);
}

// L_diffuse = C_object * C_light * I_light * max(0, surface_Normal * light_direction)
t_col	compute_diffuse_light(t_hit *hit, t_light *light)
{
	t_col		diffcol;
	t_vector	light_direction;
	double		ND;

	light_direction = vector_subtraction(&light->position, &hit->position);
	light_direction = vector_normalization(&light_direction);
	ND = vector_dot(&hit->normal, &light_direction);
	ND = fmax(0.0, ND);
	diffcol = color_mult(hit->local_color, light->color);
	diffcol.red *= light->brightness * ND;
	diffcol.green *= light->brightness * ND;
	diffcol.blue *= light->brightness * ND;
	return (diffcol);
}
