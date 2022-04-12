/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 15:52:24 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/12 17:44:05 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "colors.h"

static void	draw_square(mlx_image_t *img, t_loc loc, int size, int color)
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

void	draw_player(t_gameinfo *gameinfo)
{
	t_loc	loc;

	loc.x = 0;
	loc.y = 0;
	draw_square(gameinfo->player_img, loc, gameinfo->size * 0.8, BLUE);
}

static void	draw_exit_and_collectables(t_gameinfo *gameinfo)
{
	int		i;
	int		j;
	t_loc	loc;

	i = 0;
	while (i < gameinfo->height)
	{
		loc.y = i * gameinfo->size + gameinfo->size / 10;
		j = 0;
		while (j < gameinfo->width)
		{
			loc.x = j * gameinfo->size + gameinfo->size / 10;
			if (gameinfo->map[i][j] == 'E')
				draw_square(gameinfo->img, loc, gameinfo->size * 0.8, YELLOW);
			if (gameinfo->map[i][j] == 'C')
				draw_square(gameinfo->img, loc, gameinfo->size * 0.8, RED);
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
	while (i < gameinfo->height)
	{
		loc.y = i * gameinfo->size;
		j = 0;
		while (j < gameinfo->width)
		{
			loc.x = j * gameinfo->size;
			if (gameinfo->map[i][j] == '1' || (gameinfo->map[i][j] == 'E' && \
				gameinfo->c_count != gameinfo->player.c_found))
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
	draw_exit_and_collectables(gameinfo);
}
