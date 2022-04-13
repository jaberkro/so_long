/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 14:01:18 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/13 14:08:09 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_data *data, int x, int y, char c)
{
	data->map[data->map_loc.y][data->map_loc.x] = '0';
	data->map_loc.y += y;
	data->map_loc.x += x;
	data->moves++;
	data->map[data->map_loc.y][data->map_loc.x] = c;
}

int	char_here(t_data *data, int x, int y, char c)
{
	int	x_check;
	int	y_check;

	x_check = data->map_loc.x + x;
	y_check = data->map_loc.y + y;
	if (data->map[y_check][x_check] == c)
		return (1);
	return (0);
}

void	update_map(int x, int y, void **input, int *done)
{
	t_data	*data;
	int		place;

	data = *input;
	if (char_here(data, x, y, '1') || (char_here(data, x, y, 'E') && \
		data->c_found != data->c_count))
		return ;
	if (char_here(data, x, y, 'E') && \
		data->c_found == data->c_count)
	{
		move_player(data, x, y, 'E');
		*done = 1;
	}
	else if (!char_here(data, x, y, 'E'))
	{
		if (char_here(data, x, y, 'C'))
			data->c_found++;
		move_player(data, x, y, 'P');
		draw_image(data);
	}
	place = data->map_loc.x * data->size + data->size / 10;
	data->p_img->instances[0].x = place;
	place = data->map_loc.y * data->size + data->size / 10;
	data->p_img->instances[0].y = place;
	ft_printf("moves: %d\n", data->moves);
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	int		done;
	t_data	*data;

	data = param;
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
		mlx_close_window(data->mlx);
}

int32_t	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2 || correct_extension(argv[1], ".ber") != 0)
		exit_with_message("Error\nTry: ./so_long your_map_name.ber");
	init_data(&data, argv[1]);
	init_mlx_and_images(&data);
	draw_image(&data);
	draw_player(&data);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_image_to_window(data.mlx, data.p_img, data.img_loc.x, data.img_loc.y);
	mlx_key_hook(data.mlx, &my_keyhook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	exit(EXIT_SUCCESS);
}
