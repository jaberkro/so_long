/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 15:13:28 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/13 14:09:38 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "MLX42.h"
# include "libft.h"

typedef struct s_loc{
	int	x;
	int	y;
}	t_loc;

typedef struct s_data{
	int			width;
	int			height;
	int			size;
	char		**map;
	int			p_count;
	int			e_count;
	int			c_count;
	int			c_found;
	int			moves;
	t_loc		map_loc;
	t_loc		img_loc;
	mlx_image_t	*img;
	mlx_image_t	*p_img;
	mlx_t		*mlx;
}	t_data;

char	*scan_file(char *filename);
void	init_data(t_data *data, char *filename);
void	init_mlx_and_images(t_data *data);
void	check_map(t_data *data);
int		correct_extension(char *check, char *end);
int		is_valid(char c);
void	exit_with_message(char *message);
void	draw_image(t_data *data);
void	draw_player(t_data *data);

#endif
