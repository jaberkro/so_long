/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 15:52:24 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/04 21:57:04 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "colors.h"

void	draw_square(mlx_image_t *img, t_loc loc, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(img, loc.x + j, loc.y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_foreground(t_gameinfo *gameinfo)
{
	int		i;
	int		j;
	t_loc	loc;

	i = 0;
	while (i < gameinfo->h)
	{
		loc.y = i * gameinfo->size + gameinfo->size / 10;
		j = 0;
		while (j < gameinfo->w)
		{
			loc.x = j * gameinfo->size + gameinfo->size / 10;
			if (gameinfo->map[i][j] == 'P')
				draw_square(gameinfo->img, loc, gameinfo->size * 0.8, BLUE);
			if (gameinfo->map[i][j] == 'C')
				draw_square(gameinfo->img, loc, gameinfo->size * 0.8, RED);
			if (gameinfo->map[i][j] == 'E')
				draw_square(gameinfo->img, loc, gameinfo->size * 0.8, YELLOW);
			j++;
		}
		i++;
	}
}

static void	draw_background(t_gameinfo *gameinfo)
{
	int		i;
	int		j;
	t_loc	loc;

	i = 0;
	while (i < gameinfo->h)
	{
		loc.y = i * gameinfo->size;
		j = 0;
		while (j < gameinfo->w)
		{
			loc.x = j * gameinfo->size;
			if (gameinfo->map[i][j] == '1' || (gameinfo->map[i][j] == 'E' && \
				gameinfo->c != gameinfo->player.c_found))
				draw_square(gameinfo->img, loc, gameinfo->size, BLACK);
			else
				draw_square(gameinfo->img, loc, gameinfo->size, WHITE);
			j++;
		}
		i++;
	}
}

void	draw_image(t_gameinfo *gameinfo)
{
	draw_background(gameinfo);
	draw_foreground(gameinfo);
}
