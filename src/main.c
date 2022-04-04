/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 14:01:18 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/04 22:35:55 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

void	move_player(t_gameinfo *ginfo, int x, int y, char c)
{
	ginfo->map[ginfo->player.py][ginfo->player.px] = '0';
	ginfo->player.py += y;
	ginfo->player.px += x;
	ginfo->player.moves++;
	ginfo->map[ginfo->player.py][ginfo->player.px] = c;
}

void	update_map(int x, int y, void **input, int *done)
{
	t_gameinfo	*ginfo;
	int			i;

	i = 0;
	ginfo = *input;
	if (ginfo->map[ginfo->player.py + y][ginfo->player.px + x] != '1')
	{
		if (ginfo->map[ginfo->player.py + y][ginfo->player.px + x] == 'E')
		{
			if (ginfo->player.c_found == ginfo->c)
			{
				move_player(ginfo, x, y, 'E');
				*done = 1;
			}
		}
		else
		{
			if (ginfo->map[ginfo->player.py + y][ginfo->player.px + x] == 'C')
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
		mlx_close_window(gameinfo->mlx);
}

void	update_size(int32_t width, int32_t height, void *param)
{
	t_gameinfo	*gameinfo;

	gameinfo = param;
	if (width / gameinfo->w > height / gameinfo->h)
		gameinfo->size = height / gameinfo->h;
	else
		gameinfo->size = width / gameinfo->w;
	if (!mlx_resize_image(gameinfo->img, width, height))
		exit(EXIT_FAILURE);
	draw_image(gameinfo);
	mlx_image_to_window(gameinfo->mlx, gameinfo->img, 0, 0);
}

int32_t	main(int argc, char **argv)
{
	int			fd;
	t_gameinfo	g;

	if (argc != 2)
		return (error_message("Format:\n./so_long yourMapname.ber\n"));
	fd = open(argv[1], O_RDONLY);
	init_gameinfo(&g, fd);
	close(fd);
	if (!g.map)
		return (EXIT_FAILURE);
	g.mlx = mlx_init(g.w * g.size, g.h * g.size, "SO_LONG", true);
	if (!g.mlx)
		exit(EXIT_FAILURE);
	g.img = mlx_new_image(g.mlx, g.w * g.size, g.h * g.size);
	if (!g.img)
		exit(EXIT_FAILURE);
	draw_image(&g);
	mlx_image_to_window(g.mlx, g.img, 0, 0);
	mlx_key_hook(g.mlx, &my_keyhook, &g);
	mlx_resize_hook(g.mlx, &update_size, &g);
	mlx_loop(g.mlx);
	mlx_terminate(g.mlx);
	free_return_map(&g);
	return (EXIT_SUCCESS);
}
