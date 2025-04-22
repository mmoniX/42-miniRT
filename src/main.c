/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:55:42 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/22 17:13:50 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	exit_hook(void *param)
{
	t_map	*map;

	map = param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(map->mlx);
		exit(0);
	}
}

int	main(int argc, char *argv[])
{
	t_map	*map;

	if (argc != 2 || check_file(argv[1]) != 0)
	{
		printf("Usage: ./miniRT <filename.rt>\n");
		return (FAIL);
	}
	map = map_initialization();
	if (!map)
		return (FAIL);
	mlx_loop_hook(map->mlx, &exit_hook, map);
	mlx_loop(map->mlx);
	return (SUCCESS);
}
