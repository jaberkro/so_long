/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 14:01:18 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/09 18:36:27 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_gameinfo *ginfo, int x, int y, char c)
{
	ginfo->map[ginfo->player.posy][ginfo->player.posx] = '0';
	ginfo->player.posy += y;
	ginfo->player.posx += x;
	ginfo->player.moves++;
	ginfo->map[ginfo->player.posy][ginfo->player.posx] = c;
}

void	update_map(int x, int y, void **input, int *done)
{
	t_gameinfo	*ginfo;
	int			i;

	i = 0;
	ginfo = *input;
	if (ginfo->map[ginfo->player.posy + y][ginfo->player.posx + x] != '1')
	{
		if (ginfo->map[ginfo->player.posy + y][ginfo->player.posx + x] == 'E')
		{
			if (ginfo->player.c_found == ginfo->c_count)
			{
				move_player(ginfo, x, y, 'E');
				*done = 1;
			}
		}
		else
		{
			if (ginfo->map[ginfo->player.posy + y][ginfo->player.posx + x] == 'C')
				ginfo->player.c_found++;
			move_player(ginfo, x, y, 'P');
		}
		draw_image(ginfo);
		mlx_image_to_window(ginfo->mlx, ginfo->img, 0, 0);
		ft_printf("moves:%d\n", ginfo->player.moves);
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
	{
		mlx_close_window(gameinfo->mlx);
	}
}

void	update_size(int32_t width, int32_t height, void *param)
{
	t_gameinfo	*gameinfo;

	gameinfo = param;
	if (width / gameinfo->width > height / gameinfo->height)
		gameinfo->size = height / gameinfo->height;
	else
		gameinfo->size = width / gameinfo->width;
	if (!mlx_resize_image(gameinfo->img, width, height))
		exit(EXIT_FAILURE);
	draw_image(gameinfo);
	mlx_image_to_window(gameinfo->mlx, gameinfo->img, 0, 0);
}

int32_t	main(int argc, char **argv)
{
	t_gameinfo	gameinfo;
	int			mlx_width;
	int			mlx_height;

	if (argc != 2 || correct_extension(argv[1], ".ber") != 0)
		exit_with_message("Error\nTry: ./so_long yourMapname.ber");
	init_gameinfo(&gameinfo, argv[1]);
	mlx_width = gameinfo.width * gameinfo.size;
	mlx_height = gameinfo.height * gameinfo.size;
	gameinfo.mlx = mlx_init(mlx_width, mlx_height, "SO_LONG", true);
	if (!gameinfo.mlx)
		exit_with_message("Error\nCreating mlx failed");
	gameinfo.img = mlx_new_image(gameinfo.mlx, mlx_width, mlx_height);
	if (!gameinfo.img)
		exit_with_message("Error\nCreating new image failed");
	draw_image(&gameinfo);
	mlx_image_to_window(gameinfo.mlx, gameinfo.img, 0, 0);
	mlx_key_hook(gameinfo.mlx, &my_keyhook, &gameinfo);
	mlx_resize_hook(gameinfo.mlx, &update_size, &gameinfo);
	mlx_loop(gameinfo.mlx);
	mlx_terminate(gameinfo.mlx);
	exit(EXIT_SUCCESS);
}
