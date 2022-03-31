/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 14:01:18 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/03/31 19:43:34 by jaberkro      ########   odam.nl         */
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

void	update_map(int x, int y, void **input, int *done)
{
	t_gameinfo *gameinfo;
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*background;
	int			i;

	i = 0;
	gameinfo = *input;
	mlx = *(gameinfo->mlx);
	map = *(gameinfo->map);
	background = *(gameinfo->background);
	if (map->map[map->py + y][map->px + x] != '1')
	{
		if (map->map[map->py + y][map->px + x] == 'E')
		{
		 	if (map->c_found == map->c_count)
			{
				map->map[map->py][map->px] = '0';
				map->py += y;
				map->px += x;
				map->map[map->py][map->px] = 'E';
				*done = 1;	
				ft_printf("win!\n");
			}
		}
		else 
		{
			if (map->map[map->py + y][map->px + x] == 'C')
				map->c_found++;
			map->map[map->py][map->px] = '0';
			map->py += y;
			map->px += x;
			map->map[map->py][map->px] = 'P';
		}
		draw_background(background, map, MULT);
		mlx_image_to_window(mlx, background, 0, 0);
		
	}
}

void	hook(void *input)
{
	t_gameinfo *gameinfo;
	mlx_t		*param;
	t_map		*map;
	mlx_image_t	*background;
	int			done;

	done = 0;
	gameinfo = input;
	param = *(gameinfo->mlx);
	map = *(gameinfo->map);
	background = *(gameinfo->background);
	if (mlx_is_key_down(param, MLX_KEY_UP))
		update_map(0, -1, &input, &done);
	if (mlx_is_key_down(param, MLX_KEY_DOWN))
		update_map(0, 1, &input, &done);
	if (mlx_is_key_down(param, MLX_KEY_LEFT))
		update_map(-1, 0, &input, &done);
	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
		update_map(1, 0, &input, &done);
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))// || done)
		mlx_close_window(param);
}

int32_t	main(void)
{
	mlx_t		*mlx;
	int			fd;
	t_map		*this_map;
	mlx_image_t	*background;
	t_gameinfo	*gameinfo;

	fd = open("maps/map1.ber", O_RDONLY);
	this_map = init_map(fd);
	if (!this_map)
		return (1);
	// ft_printf("mapvalues:\nwidth: %d\nheight: %d\nmap:\n%s\n%s\n%s\n%s\n%s\n%s\n", this_map->width, this_map->height, this_map->map[0], this_map->map[1], this_map->map[2], this_map->map[3], this_map->map[4], this_map->map[5]);
	mlx = mlx_init(this_map->width * MULT, this_map->height * MULT, "SO_LONG", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	gameinfo = malloc(sizeof(t_gameinfo));
	if (!gameinfo)
		return (1);
	background = mlx_new_image(mlx, this_map->width * MULT, this_map->height * MULT);
	gameinfo->mlx = &mlx;
	gameinfo->map = &this_map;
	gameinfo->background = &background;
	draw_background(background, this_map, MULT);
	mlx_image_to_window(mlx, background, 0, 0);
	mlx_loop_hook(mlx, &hook, gameinfo);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
