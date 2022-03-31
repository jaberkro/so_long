/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 15:52:24 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/03/31 17:28:03 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "so_long.h"

void    draw_square(mlx_image_t* img, float x, float y, int size, int color)
{
    int i;
    int j;

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

void    draw_background(mlx_image_t* img, t_map *map, int size)
{
    int i;
    int j;

    i = 0;
    while (i < map->height)
    {
        j = 0;
        while (j < map->width)
        {
            if (map->map[i][j] == '1')
                draw_square(img, j * size, i * size, size, 0xff00ffff);
            else
                draw_square(img, j * size, i * size, size, 0x00ff00ff);
            if (map->map[i][j] == 'P')
                draw_square(img, j * size + size / 10, i * size + size / 10, size * 0.8, 0x0000ffff);
            if (map->map[i][j] == 'C')
                draw_square(img, j * size + size / 10, i * size + size / 10, size * 0.8, 0xff0000ff);
             if (map->map[i][j] == 'E')
                draw_square(img, j * size + size / 10, i * size + size / 10, size * 0.8, 0xffffffff);
            j++;
        }
        i++;
    }
}
