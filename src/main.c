/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:55:42 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/30 18:43:31 by mmonika          ###   ########.fr       */
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
	t_map		*map;
	t_mrt		mrt;
	t_col		col;
	t_vector	position;

	if (argc != 2 || check_file(argv[1]) != 0)
	{
		printf("Usage: ./miniRT <filename.rt>\n");
		return (FAIL);
	}
	map = map_initialization();
	if (!map)
		return (FAIL);
	init_mrt(&mrt, &col, &position);
	parsing(argv[1], &mrt);
	
	printf("\n<---------Ambient Details------->\n");
	printf("Ambient ratio: %lf\n", mrt.amb.ratio);
	printf("Ambient color: R=%d, G=%d, B=%d\n",
		mrt.amb.color.red, mrt.amb.color.green, mrt.amb.color.blue);	
	
	printf("\n<---------Camera Details------->\n");
	printf("Camera Position: X=%lf, Y=%lf, Z=%lf\n",
		mrt.camera.position.x, mrt.camera.position.y, mrt.camera.position.z);	
	printf("Camera Normal: X=%lf, Y=%lf, Z=%lf\n",
		mrt.camera.normal.x, mrt.camera.normal.y, mrt.camera.normal.z);	
	printf("Camera FOV: %f\n", mrt.camera.fov);	
	
	printf("\n<---------Light Details------->\n");
	printf("Light Position: X=%lf, Y=%lf, Z=%lf\n",
		mrt.light.position.x, mrt.light.position.y, mrt.light.position.z);
	printf("Light Brightness: %f\n", mrt.light.brightness);	
	printf("Light Color:  R=%d, G=%d, B=%d\n",
		mrt.light.color.red, mrt.light.color.green, mrt.light.color.blue);	

	printf("\n<---------Plane Details------->\n");
	printf("Plane Position: X=%lf, Y=%lf, Z=%lf\n",
		mrt.plane.position.x, mrt.plane.position.y, mrt.plane.position.z);
	printf("Plane Normal: X=%lf, Y=%lf, Z=%lf\n",
			mrt.plane.normal.x, mrt.plane.normal.y, mrt.plane.normal.z);	
	printf("Plane Color:  R=%d, G=%d, B=%d\n",
		mrt.plane.color.red, mrt.plane.color.green, mrt.plane.color.blue);	
	
	printf("\n<---------Sphere Details------->\n");
	printf("Sphere Position: X=%lf, Y=%lf, Z=%lf\n",
		mrt.sp.position.x, mrt.sp.position.y, mrt.sp.position.z);
	printf("Sphere diameter: %f\n", mrt.sp.diameter);
	printf("sphere Color:  R=%d, G=%d, B=%d\n",
		mrt.sp.color.red, mrt.sp.color.green, mrt.sp.color.blue);	
		
	printf("\n<---------Cylinder Details------->\n");
	printf("Cylinder Position: X=%lf, Y=%lf, Z=%lf\n",
		mrt.cyl.position.x, mrt.cyl.position.y, mrt.cyl.position.z);	
	printf("Cylinder Normal: X=%lf, Y=%lf, Z=%lf\n",
		mrt.cyl.normal.x, mrt.cyl.normal.y, mrt.cyl.normal.z);	
	printf("Cylinder diameter: %f\n", mrt.cyl.diameter);
	printf("Cylinder height: %f\n", mrt.cyl.height);
	printf("Cylinder Color:  R=%d, G=%d, B=%d\n",
		mrt.cyl.color.red, mrt.cyl.color.green, mrt.cyl.color.blue);
	
	mlx_loop_hook(map->mlx, &exit_hook, map);
	mlx_loop(map->mlx);
	
	return (SUCCESS);
}
