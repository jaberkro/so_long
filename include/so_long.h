/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 15:13:28 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/03/31 16:02:01 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct s_map{
	int		p_count;
	int		c_count;
	int		e_count;
	int		width;
	int 	height;
	char	**map;
}       t_map;

char	*scan_file(int fd);
t_map	*init_map(int fd);
int		error_check(t_map *this_map);


void draw_rectangle(mlx_image_t* img, float x, float y, int w, int h);


char	get_char(int fd);

#endif