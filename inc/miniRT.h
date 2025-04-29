/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:19:17 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/29 18:57:03 by gahmed           ###   ########.fr       */
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

typedef	struct s_amb
{
	float	ratio;
	t_col	color;
}	t_amb;

typedef struct s_cam
{
	t_vector	position;
	float		fov;
}	t_cam;

typedef struct s_light
{
	float		ratio;
	t_vector	pos;
	t_col		color;
}	t_light;
typedef struct s_plane
{
	t_vector	position;
	t_col		color;
}	t_plane;

typedef struct s_sphere
{
	t_vector	position;
	float		radius;
	t_col		color;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector	position;
	float		radius;
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
int			is_valid_ratio(char *str);
int			is_valid_rgb(char *str);

/* init */
int			check_file(char *filename);
void init_mrt(t_mrt *mrt, t_col *col, t_vector *position);

/* utils */
t_map		*map_initialization(void);
float		ft_atof(const char *str);

/* vector */
t_vector	vector_addition(t_vector *a, t_vector *b);
t_vector	vector_subtraction(t_vector *a, t_vector *b);
double		vector_magnitude(t_vector *a, t_vector *b);

/* parsing */
void	parsing(char *filename, t_mrt *mrt);

/* main */
void		exit_hook(void *param);

#endif