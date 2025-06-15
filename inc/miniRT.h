/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:19:17 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/15 14:06:10 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"

# define SUCCESS	0
# define FAIL		1
# define TRUE		1
# define FALSE		0
# define WIDTH		1200
# define HEIGHT		800
# define SIZE		100
# define DEF_SHINE  5
# define REF		0.5
# define BIAS		0.001

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_col
{
	int	red;
	int	green;
	int	blue;
}	t_col;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
	int			depth;
}	t_ray;

typedef struct s_amb
{
	float	ratio;
	t_col	color;
}	t_amb;

typedef struct s_cam
{
	t_vector	position;
	t_vector	normal;
	float		fov;
}	t_cam;

typedef struct s_light
{
	t_vector	position;
	float		brightness;
	t_col		color;
}	t_light;

typedef struct s_plane
{
	t_vector	position;
	t_vector	normal;
	t_col		color;
}	t_plane;

typedef struct s_sphere
{
	t_vector	position;
	float		diameter;
	t_col		color;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector	position;
	t_vector	normal;
	t_vector	cap1;
	t_vector	cap2;
	float		diameter;
	float		height;
	t_col		color;
}	t_cylinder;

typedef struct s_quadratic
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t1;
	float	t2;
}	t_quadratic;

typedef struct s_hit
{
	double			distance;
	t_vector		position;
	t_vector		normal;
	t_ray			*ray;
	t_sphere		*sp;
	t_plane			*pl;
	t_cylinder		*cy;
	t_col			local_color;
}					t_hit;

typedef struct s_mrt
{
	t_col		color;
	t_amb		amb;
	t_cam		camera;
	t_light		light;
	t_plane		*plane;
	int			plane_count;
	t_sphere	*sp;
	int			sp_count;
	t_cylinder	*cyl;
	int			cyl_count;
	t_hit		*hit;
}	t_mrt;

typedef struct s_map
{
	unsigned int	width;
	unsigned int	height;
	t_amb			ambient;
	mlx_t			*mlx;
	mlx_image_t		*image;
}	t_map;

/* check */
int			check_file(char *filename);
int			is_valid_normal(t_vector vec, float min, float max);
int			is_valid_rgb(t_col col, int min, int max);

/* colour */
t_col		c_mult(t_col a, t_col b);
t_col		c_add(t_col a, t_col b);
t_col		c_m_sca(t_col a, double n);

/* cylinder */
double		cy_cap_hit(t_ray *ray, t_vector cen, t_vector cap_norm, double rad);
void		cylinder_caps_hit(t_ray	*ray, t_cylinder *cyl, double *t_min);
t_quadratic	cyl_eq(t_ray *ray, t_cylinder *cyl);
double		intersect_cylinder(t_ray *ray, t_cylinder *cyl);

/* hit */
t_vector	hit_sphere(t_ray *ray, t_sphere *sp, double t);
int			sp_hit_info(t_ray *ray, t_sphere *sp, t_hit *hit);
int			pl_hit_info(t_ray *ray, t_plane *pl, t_hit *hit);
t_vector	hit_cylinder(t_ray *ray, t_cylinder *cyl, double t);
int			cyl_hit_info(t_ray *ray, t_cylinder *cyl, t_hit *hit);

/* init */
t_map		*map_initialization(void);
void		init_mrt(t_mrt *mrt, t_col *col, t_vector *position);

/* light */
t_col		calculate_light(t_hit *hit, t_mrt *mrt);
t_col		compute_amb(t_hit *hit, t_amb *amb);
t_col		compute_diff(t_hit *hit, t_light *light);
t_col		compute_spec(t_hit *hit, t_light *light, t_cam *cam);
void		compute_ref(t_hit *hit, t_ray *ref_ray);

/* main */
void		exit_hook(void *param);

/* parse_obj */
void		parse_logic(char *line, t_mrt *mrt);
void		parsing(char *filename, t_mrt *mrt);
void		parse_plane(char **tokens, t_mrt *mrt);
void		parse_sphere(char **tokens, t_mrt *mrt);
void		parse_cylinder(char **tokens, t_mrt *mrt);

/* parse_utils */
t_vector	parse_point(char *tokens);
t_col		parse_color(char *tokens);
void		parse_ambient(char **tokens, t_mrt *mrt);
void		parse_camera(char **tokens, t_mrt *mrt);
void		parse_light(char **tokens, t_mrt *mrt);

/* ray_tracing */
t_col		trace_ray(t_ray *ray, t_mrt *mrt);
double		intersect_sphere(t_ray *ray, t_sphere *sphere);
double		intersect_plane(t_ray *ray, t_plane *plane);
t_quadratic	solve_quadratic(double a, double b, double c);
void		obj_intersect(t_ray *ray, t_mrt *mrt, t_hit *hit);

/* render */
void		clear_background(mlx_image_t *image);
void		set_background(t_mrt *mrt, double *v0, double *v1);
t_vector	ray_res(t_mrt *mrt, double u, double v, t_vector uu_w);
t_ray		generate_ray(t_mrt *mrt, int x, int y);
void		rendering(t_map *map, t_mrt *mrt);

/* shadow */
t_vector	random_light(t_light *light);
int			ft_soft_shadow(t_hit *hit, t_mrt *mrt, int samples);

/* utils */
float		ft_atof(const char *str);
void		free_array(char **arr);
char		*normalize_whitespace(char *str);
int			rgba_channel(t_col col);
t_col		clamp_color(t_col col);

/* vector1 */
t_vector	v_add(t_vector a, t_vector b);
t_vector	v_sub(t_vector a, t_vector b);
double		v_mag(t_vector *a, t_vector *b);
double		v_dot(t_vector a, t_vector b);
t_vector	v_norm(t_vector a);

/* vector2 */
t_vector	v_m_sca(t_vector *a, double n);
t_vector	v_cross(t_vector *a, t_vector *b);
double		v_length(t_vector a);

#endif
