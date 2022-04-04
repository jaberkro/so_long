/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 15:52:24 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/04 18:32:52 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "so_long.h"

void	draw_square(mlx_image_t *img, float x, float y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_background(t_gameinfo *gameinfo)
{
	int	i;
	int	j;

	i = 0;
	while (i < gameinfo->h)
	{
		j = 0;
		while (j < gameinfo->w)
		{
			if (gameinfo->map[i][j] == '1')
				draw_square(gameinfo->img, j * gameinfo->size, i * gameinfo->size, gameinfo->size, 0x000000ff);
			else
				draw_square(gameinfo->img, j * gameinfo->size, i * gameinfo->size, gameinfo->size, 0xffffffff);
			if (gameinfo->map[i][j] == 'P')
				draw_square(gameinfo->img, j * gameinfo->size + gameinfo->size / 10, i * gameinfo->size + gameinfo->size / 10, gameinfo->size * 0.8, 0x0000ffff);
			if (gameinfo->map[i][j] == 'C')
				draw_square(gameinfo->img, j * gameinfo->size + gameinfo->size / 10, i * gameinfo->size + gameinfo->size / 10, gameinfo->size * 0.8, 0xffee00ff);
			if (gameinfo->map[i][j] == 'E')
				draw_square(gameinfo->img, j * gameinfo->size + gameinfo->size / 10, i * gameinfo->size + gameinfo->size / 10, gameinfo->size * 0.8, 0xff0000ff);
			j++;
		}
		i++;
	}
}
