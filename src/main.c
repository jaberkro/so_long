/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 14:01:18 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/04 18:41:22 by jaberkro      ########   odam.nl         */
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

void	update_map(int x, int y, void **input, int *done)
{
	t_gameinfo	*gameinfo;
	int			i;

	i = 0;
	gameinfo = *input;
	if (gameinfo->map[gameinfo->player.py + y][gameinfo->player.px + x] != '1')
	{
		if (gameinfo->map[gameinfo->player.py + y][gameinfo->player.px + x] == 'E')
		{
			if (gameinfo->player.c_found == gameinfo->c)
			{
				gameinfo->map[gameinfo->player.py][gameinfo->player.px] = '0';
				gameinfo->player.py += y;
				gameinfo->player.px += x;
				gameinfo->map[gameinfo->player.py][gameinfo->player.px] = 'E';
				gameinfo->player.moves++;
				*done = 1;
			}
		}
		else
		{
			if (gameinfo->map[gameinfo->player.py + y][gameinfo->player.px + x] == 'C')
				gameinfo->player.c_found++;
			gameinfo->map[gameinfo->player.py][gameinfo->player.px] = '0';
			gameinfo->player.py += y;
			gameinfo->player.px += x;
			gameinfo->map[gameinfo->player.py][gameinfo->player.px] = 'P';
			gameinfo->player.moves++;
		}
		draw_background(gameinfo);
		mlx_image_to_window(gameinfo->mlx, gameinfo->img, 0, 0);
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	int			done;
	t_gameinfo	*gameinfo;

	gameinfo = param;
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
		mlx_close_window(gameinfo->mlx);
	if (keydata.action == MLX_PRESS)
		ft_printf("movements:%d\n", gameinfo->player.moves);
}

int32_t	main(void)
{
	int			fd;
	t_gameinfo	gameinfo;

	fd = open("maps/map1.ber", O_RDONLY);
	init_gameinfo(&gameinfo, fd);
	if (!gameinfo.map)
		return (EXIT_FAILURE);
	// print_map(gameinfo.map);
	gameinfo.mlx = mlx_init(gameinfo.w * gameinfo.size, gameinfo.h * gameinfo.size, "SO_LONG", true);
	if (!gameinfo.mlx)
	 	exit(EXIT_FAILURE);
	gameinfo.img = mlx_new_image(gameinfo.mlx, gameinfo.w * gameinfo.size, gameinfo.h * gameinfo.size);

	draw_background(&gameinfo);
	mlx_image_to_window(gameinfo.mlx, gameinfo.img, 0, 0);
	mlx_key_hook(gameinfo.mlx, &my_keyhook, &gameinfo);
	mlx_loop(gameinfo.mlx);
	mlx_terminate(gameinfo.mlx);
	return (EXIT_SUCCESS);
}
