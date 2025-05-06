/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:19:17 by mmonika           #+#    #+#             */
/*   Updated: 2025/05/06 16:45:41 by mmonika          ###   ########.fr       */
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
# define WIDTH		800
# define HEIGHT		400

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

typedef struct s_mrt
{
	t_col		color;
	t_amb		amb;
	t_cam		camera;
	t_light		light;
	t_plane		plane;
	t_sphere	sp;
	t_cylinder	cyl;
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
int			is_valid_normal(t_vector vec, float min, float max);
int			is_valid_rgb(t_col col, int min, int max);

/* init */
int			check_file(char *filename);
void		init_mrt(t_mrt *mrt, t_col *col, t_vector *position);

/* utils */
t_map		*map_initialization(void);
float		ft_atof(const char *str);
void		free_array(char **arr);
char		*normalize_whitespace(char *str);
int			rgba_channel(t_col col);

/* vector */
t_vector	vector_addition(t_vector *a, t_vector *b);
t_vector	vector_subtraction(t_vector *a, t_vector *b);
double		vector_magnitude(t_vector *a, t_vector *b);

/* parse_obj */
void		parse_plane(char **tokens, t_mrt *mrt);
void		parse_sphere(char **tokens, t_mrt *mrt);
void		parse_cylinder(char **tokens, t_mrt *mrt);

/* parse_utils */
t_vector	parse_point(char *tokens);
t_col		parse_color(char *tokens);
void		parsing(char *filename, t_mrt *mrt);
void		parse_ambient(char **tokens, t_mrt *mrt);
void		parse_camera(char **tokens, t_mrt *mrt);

/* render */
void		clear_background(mlx_image_t *image);
void		rendering(t_map *map);

/* main */
void		exit_hook(void *param);

#endif