/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:02:46 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/14 17:45:18 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// Color = Ambient + (1 - in_shadow) * (Diffuse + Specular)
t_col	calculate_light(t_hit *hit, t_mrt *mrt)
{
	t_col	final_color;
	t_col	amb_light;
	t_col	diff_spec_light;
	double	shadow;

	amb_light = compute_amb(hit, &mrt->amb);
	diff_spec_light = c_add(compute_diff(hit, &mrt->light),
			compute_spec(hit, &mrt->light, &mrt->camera));
	shadow = ft_soft_shadow(hit, mrt, 16);
	final_color = c_add(amb_light, c_m_sca(diff_spec_light, 1.0 - shadow));
	return (final_color);
}

//L_ambient = C_object * C_ambient_light * I_ambient
t_col	compute_amb(t_hit *hit, t_amb *amb)
{
	t_col	ambcol;

	ambcol = c_mult(hit->local_color, amb->color);
	ambcol = c_m_sca(ambcol, amb->ratio);
	return (ambcol);
}

// L_diff = C_obj * C_light * I_light * max(0, s_Normal * l_dir)
t_col	compute_diff(t_hit *hit, t_light *light)
{
	t_col		diffcol;
	t_vector	l_dir;
	double		nd;

	l_dir = v_norm(v_sub(light->position, hit->position));
	nd = fmax(0, v_dot(hit->normal, l_dir));
	diffcol = c_m_sca(c_mult(hit->local_color, light->color),
			(light->brightness * nd));
	return (diffcol);
}

//L_spec = C_light * I_light * (max(0, ref_l_dir * view_dir))^shininess
//ref_l_dir = 2 * (s_Normal * l_dir) * s_Normal - l_dir
t_col	compute_spec(t_hit *hit, t_light *light, t_cam *cam)
{
	t_col		speccol;
	t_vector	l_dir;
	t_vector	view_dir;
	t_vector	ref_l_dir;
	double		rv;

	l_dir = v_norm(v_sub(light->position, hit->position));
	ref_l_dir = v_sub(v_m_sca(&hit->normal,
				2 * v_dot(hit->normal, l_dir)), l_dir);
	view_dir = v_norm(v_sub(cam->position, hit->position));
	rv = pow(fmax(0, v_dot(ref_l_dir, view_dir)), DEF_SHINE);
	rv = fmin(rv, 1.0);
	speccol = c_m_sca(light->color, (light->brightness * rv));
	return (speccol);
}

//ref = hit->ray->dir - 2 * (s_Normal * hit->ray->dir) * s_Normal
void	compute_ref(t_hit *hit, t_ray *ref_ray)
{
	t_vector	ref_l_dir;

	ref_l_dir = v_sub(hit->ray->direction, v_m_sca(&hit->normal,
		2 * v_dot(hit->normal, hit->ray->direction)));
	ref_ray->origin = v_add(hit->position, v_m_sca(&hit->normal, BIAS));
	ref_ray->direction = ref_l_dir;
	ref_ray->depth = hit->ray->depth + 1;
}
