/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 15:52:24 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/03/31 16:05:20 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"

void draw_rectangle(mlx_image_t* img, float x, float y, int w, int h)
{
    int i;
    int j;

    i = 0;
    while (i < h)
    {
        j = 0;
        while (j < w)
        {
            mlx_put_pixel(img, x + j, y + i, 0);
            j++;
        }
        i++;
    }

}
