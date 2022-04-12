/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 14:01:18 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/12 17:59:02 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_gameinfo *gameinfo, int x, int y, char c)
{
	gameinfo->map[gameinfo->player.posy][gameinfo->player.posx] = '0';
	gameinfo->player.posy += y;
	gameinfo->player.posx += x;
	gameinfo->player.moves++;
	gameinfo->map[gameinfo->player.posy][gameinfo->player.posx] = c;
}

int	char_found_on_map(t_gameinfo *gameinfo, int x, int y, char c)
{
	int	x_check;
	int	y_check;

	x_check = gameinfo->player.posx + x;
	y_check = gameinfo->player.posy + y;
	if (gameinfo->map[y_check][x_check] == c)
		return (1);
	return (0);
}

void	update_map(int x, int y, void **input, int *done)
{
	t_gameinfo	*gameinfo;
	int			play_x;
	int			play_y;

	gameinfo = *input;
	if (char_found_on_map(gameinfo, x, y, '1'))
		return ;
	if (char_found_on_map(gameinfo, x, y, 'E') && \
		gameinfo->player.c_found == gameinfo->c_count)
	{
		move_player(gameinfo, x, y, 'E');
		*done = 1;
	}
	else if (!char_found_on_map(gameinfo, x, y, 'E'))
	{
		if (char_found_on_map(gameinfo, x, y, 'C'))
			gameinfo->player.c_found++;
		move_player(gameinfo, x, y, 'P');
		draw_image(gameinfo);
	}
	play_x = gameinfo->player.posx * gameinfo->size + gameinfo->size * 0.1;
	play_y = gameinfo->player.posy * gameinfo->size + gameinfo->size * 0.1;
	mlx_image_to_window(gameinfo->mlx, gameinfo->img, 0, 0);
	mlx_image_to_window(gameinfo->mlx, gameinfo->player_img, play_x, play_y);
	ft_printf("moves:%d\n", gameinfo->player.moves);
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
}

int32_t	main(int argc, char **argv)
{
	t_gameinfo	gameinfo;
	int			player_x;
	int			player_y;

	if (argc != 2 || correct_extension(argv[1], ".ber") != 0)
		exit_with_message("Error\nTry: ./so_long yourMapname.ber");
	init_gameinfo(&gameinfo, argv[1]);
	player_x = gameinfo.player.posx * gameinfo.size + gameinfo.size * 0.1;
	player_y = gameinfo.player.posy * gameinfo.size + gameinfo.size * 0.1;
	init_mlx_and_images(&gameinfo);
	draw_image(&gameinfo);
	draw_player(&gameinfo);
	mlx_image_to_window(gameinfo.mlx, gameinfo.img, 0, 0);
	mlx_image_to_window(gameinfo.mlx, gameinfo.player_img, player_x, player_y);
	mlx_key_hook(gameinfo.mlx, &my_keyhook, &gameinfo);
	mlx_loop(gameinfo.mlx);
	mlx_terminate(gameinfo.mlx);
	exit(EXIT_SUCCESS);
}
