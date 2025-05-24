/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:19:17 by mmonika           #+#    #+#             */
/*   Updated: 2025/05/24 17:22:08 by mmonika          ###   ########.fr       */
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
# define MAX_SPHERES 100

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
	float		diameter;
	float		height;
	t_col		color;
}	t_cylinder;

typedef struct s_hit
{
	double			distance;
	t_vector		position;
	t_vector		normal;
	// t_vector		uvn;
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
	t_cylinder	cyl;
	int			is_sp;
	int			is_pl;
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
// double		overflow_cap(double c);
t_col 		color_mult(t_col a, t_col b);
t_col		color_add(t_col *a, t_col *b);

/* init */
t_map		*map_initialization(void);
void		init_mrt(t_mrt *mrt, t_col *col, t_vector *position);

/* light */
t_col		calculate_light(t_hit *hit, t_mrt *mrt);
t_col		compute_ambient_light(t_hit *hit, t_amb *amb);
t_col		compute_diffuse_light(t_hit *hit, t_light *light);

/* main */
void		exit_hook(void *param);

/* parse_obj */
void		parse_plane(char **tokens, t_mrt *mrt);
void		parse_sphere(char **tokens, t_mrt *mrt);
void		parse_cylinder(char **tokens, t_mrt *mrt);

/* parse_utils */
t_vector	parse_point(char *tokens);
t_col		parse_color(char *tokens);
void		parse_ambient(char **tokens, t_mrt *mrt);
void		parse_camera(char **tokens, t_mrt *mrt);
void		parse_light(char **tokens, t_mrt *mrt);
void		parsing(char *filename, t_mrt *mrt);

/* ray_tracing1 */
t_col		trace_ray(t_ray *ray, t_mrt *mrt);
double		intersect_sphere(t_ray *ray, t_sphere *sphere);
double		intersect_plane(t_ray *ray, t_plane *plane);

/* ray_tracing2 */
t_vector	hit_sphere(t_ray *ray, t_sphere *sp, double t);
int			sp_hit_info(t_ray *ray, t_sphere *sp, t_hit *hit);
int			pl_hit_info(t_ray *ray, t_plane *pl, t_hit *hit);

/* render */
void		clear_background(mlx_image_t *image);
t_ray		generate_ray(t_mrt *mrt, int x, int y);
void		rendering(t_map *map, t_mrt *mrt);

/* utils */
float		ft_atof(const char *str);
void		free_array(char **arr);
char		*normalize_whitespace(char *str);
int			rgba_channel(t_col col);
t_col		normalize_color(t_col col);

/* vector1 */
t_vector	vector_addition(t_vector *a, t_vector *b);
t_vector	vector_subtraction(t_vector *a, t_vector *b);
double		vector_magnitude(t_vector *a, t_vector *b);
double		vector_dot(t_vector *a, t_vector *b);
t_vector	vector_normalization(t_vector *a);

/* vector2 */
t_vector	vector_mult_scalar(t_vector *a, double n);
t_vector	vector_cross(t_vector *a, t_vector *b);

#endif