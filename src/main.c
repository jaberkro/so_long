/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 14:01:18 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/03/31 21:45:32 by jaberkro      ########   odam.nl         */
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

 void my_keyhook(mlx_key_data_t keydata, void* param)
{
	int			done;
	t_gameinfo	*gameinfo;
	mlx_t		*mlx;
	int			i;
	static int	steps = 0;

	i = 0;
	gameinfo = param;
	mlx = *(gameinfo->mlx);
	done = 0;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		update_map(0, -1, &param, &done);
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		update_map(0, 1, &param, &done);
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		update_map(-1, 0, &param, &done);
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		update_map(1, 0, &param, &done);
	if (done || (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS))
		mlx_close_window(mlx);
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S || \
		keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D) && 
		keydata.action == MLX_PRESS)
	{
		steps++;
		ft_printf("movements:%d\n", steps);
	}
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
	mlx_key_hook(mlx, &my_keyhook, gameinfo);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
