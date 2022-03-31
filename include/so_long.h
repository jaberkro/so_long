/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 15:13:28 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/03/31 19:07:46 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "MLX42.h"

typedef struct s_map{
	int		p_count;
	int		e_count;
	int		c_count;
	int		c_found;
	int		width;
	int 	height;
	char	**map;
	int		px;
	int		py;
}       t_map;

typedef struct s_gameinfo{
	mlx_t		**mlx;
	t_map		**map;
	mlx_image_t	**background;
}			t_gameinfo;

char	*scan_file(int fd);
t_map	*init_map(int fd);
int		error_check(t_map *this_map);


void	draw_square(mlx_image_t* img, float x, float y, int size, int color);
void	draw_background(mlx_image_t* img, t_map *map, int size);


char	get_char(int fd);

#endif