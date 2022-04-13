/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 15:52:24 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/13 14:21:03 by jaberkro      ########   odam.nl         */
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

void	draw_player(t_data *data)
{
	t_loc	loc;

	loc.x = 0;
	loc.y = 0;
	draw_square(data->p_img, loc, data->size * 0.8, BLUE);
}

static void	draw_exit_and_collectables(t_data *data)
{
	int		i;
	int		j;
	t_loc	loc;

	i = 0;
	while (i < data->height)
	{
		loc.y = i * data->size + data->size / 10;
		j = 0;
		while (j < data->width)
		{
			loc.x = j * data->size + data->size / 10;
			if (data->map[i][j] == 'E')
				draw_square(data->img, loc, data->size * 0.8, YELLOW);
			if (data->map[i][j] == 'C')
				draw_square(data->img, loc, data->size * 0.8, RED);
			j++;
		}
		i++;
	}
}

static void	draw_background(t_data *data)
{
	int		i;
	int		j;
	t_loc	loc;

	i = 0;
	while (i < data->height)
	{
		loc.y = i * data->size;
		j = 0;
		while (j < data->width)
		{
			loc.x = j * data->size;
			if (data->map[i][j] == '1' || (data->map[i][j] == 'E' && \
				data->c_count != data->c_found))
				draw_square(data->img, loc, data->size, BLACK);
			else
				draw_square(data->img, loc, data->size, WHITE);
			j++;
		}
		i++;
	}
}

void	draw_image(t_data *data)
{
	draw_background(data);
	draw_exit_and_collectables(data);
}
