/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:55:42 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/28 19:43:42 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	cleanup(t_map *map, t_mrt *mrt)
{
	if (map)
	{
		if (map->mlx)
			mlx_terminate(map->mlx);
		free(map);
		map = NULL;
	}
	if (mrt)
	{
		if (mrt->cyl)
			free(mrt->cyl);
		if (mrt->plane)
			free(mrt->plane);
		if (mrt->sp)
			free(mrt->sp);
	}
}

void	leaks_report(void)
{
	system("leaks miniRT");
}

void	exit_hook(void *param)
{
	t_map	*map;

	map = param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
	{
		cleanup(map, NULL);
		exit(0);
	}
}

int	main(int argc, char *argv[])
{
	t_map		*map;
	t_mrt		mrt;
	t_col		col;
	t_vector	position;

	atexit(leaks_report);
	if (argc != 2 || check_file(argv[1]) != 0)
	{
		if (argc != 2)
			ft_putstr_fd("Error\nUsage: ./miniRT <filename.rt>\n",
				STDERR_FILENO);
		return (FAIL);
	}
	map = map_initialization();
	if (!map)
		return (FAIL);
	init_mrt(&mrt, &col, &position);
	parsing(argv[1], &mrt);
	rendering(map, &mrt);
	mlx_loop_hook(map->mlx, &exit_hook, map);
	mlx_loop(map->mlx);
	cleanup(map, &mrt);
	return (SUCCESS);
}
