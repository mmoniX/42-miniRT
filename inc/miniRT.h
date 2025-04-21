/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:19:17 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/21 18:21:58 by mmonika          ###   ########.fr       */
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
# define WIDTH		800
# define HEIGHT		400

typedef struct s_map
{
	unsigned int	width;
	unsigned int	height;
	mlx_t			*mlx;
	mlx_image_t		*image;
}	t_map;

int		check_file(char *filename);
t_map	*map_initialization(void);

#endif