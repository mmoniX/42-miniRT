/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:02:46 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/10 14:43:51 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// Color = Ambient + (1 - in_shadow) * (Diffuse + Specular) + Reflection
t_col	calculate_light(t_hit *hit, t_mrt *mrt)
{
	t_col	final_color;
	t_col	ambient_light;
	t_col	diffuse_light;
	t_col	specular_light;
	// t_col	reflection_light;
	// t_col	phong_light (!shadow -> diffuse // reflection // !shadow -> specular)

	ambient_light = compute_ambient_light(hit, &mrt->amb);
	diffuse_light = compute_diffuse_light(hit, &mrt->light);
	specular_light = compute_specular_light(hit, &mrt->light, &mrt->camera);
	final_color.red = ambient_light.red + diffuse_light.red + specular_light.red;
	final_color.green = ambient_light.green + diffuse_light.green + specular_light.green;
	final_color.blue = ambient_light.blue + diffuse_light.blue + specular_light.blue;
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
	double		nd;

	light_direction = v_norm(v_sub(light->position, hit->position));
	nd = fmax(0, v_dot(hit->normal, light_direction));
	diffcol = color_mult(hit->local_color, light->color);
	diffcol.red *= light->brightness * nd;
	diffcol.green *= light->brightness * nd;
	diffcol.blue *= light->brightness * nd;
	return (diffcol);
}

//L_specular = C_light * I_light * (max(0, reflected_light_direction * view_direction))^shininess
//reflected_light_direction = 2 * (surface_Normal * light_direction) * surface_Normal - light_direction
t_col	compute_specular_light(t_hit *hit, t_light *light, t_cam *cam)
{
	t_col		speccol;
	t_vector	light_direction;
	t_vector	view_direction;
	t_vector	ref_light_dir;
	double		rv;
	double		nd;

	light_direction = v_norm(v_sub(light->position, hit->position));
	view_direction = v_norm(v_sub(cam->position, hit->position));
	nd = v_dot(hit->normal, light_direction);
	t_vector temp = v_m_sca(&hit->normal, 2 * nd);
	ref_light_dir = v_sub(temp, light_direction);
	rv = pow(fmax(0, v_dot(ref_light_dir, view_direction)), DEF_SHINE);
	speccol.red = light->color.red * light->brightness * rv;
	speccol.green = light->color.green * light->brightness * rv;
	speccol.blue = light->color.blue * light->brightness * rv;
	return (speccol);
}
