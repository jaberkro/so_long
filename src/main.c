/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 14:01:18 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/03/31 16:08:38 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "so_long.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <fcntl.h>

#define MULT 50

mlx_image_t	*g_img;

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
	if (mlx_is_key_down(param, MLX_KEY_UP))
		g_img->instances[0].y -= 5;
	if (mlx_is_key_down(param, MLX_KEY_DOWN))
		g_img->instances[0].y += 5;
	if (mlx_is_key_down(param, MLX_KEY_LEFT))
		g_img->instances[0].x -= 5;
	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
		g_img->instances[0].x += 5;
}

int32_t	main(void)
{
	mlx_t	*mlx;
	int		fd;
	t_map	*this_map;

	fd = open("maps/map2.ber", O_RDONLY);
	this_map = init_map(fd);
	if (!this_map)
		return (1);
	ft_printf("mapvalues:\nwidth: %d\nheight: %d\nmap:\n%s\n%s\n%s\n%s\n%s\n%s\n", this_map->width, this_map->height, this_map->map[0], this_map->map[1], this_map->map[2], this_map->map[3], this_map->map[4], this_map->map[5]);
	mlx = mlx_init(this_map->width * MULT, this_map->height * MULT, "SO_LONG", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, 128, 128);
	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	draw_rectangle(g_img, 0, 0, 40, 40);
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
