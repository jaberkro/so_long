/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 15:13:28 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/09 18:20:20 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "MLX42.h"
# include "libft.h"

typedef struct s_player{
	int	posx;
	int	posy;
	int	moves;
	int	c_found;
}	t_player;

typedef struct s_gameinfo{
	int			width;
	int			height;
	int			size;
	char		**map;
	t_player	player;
	int			p_count;
	int			c_count;
	int			e_count;
	mlx_image_t	*img;
	mlx_t		*mlx;
}	t_gameinfo;

typedef struct s_loc{
	int	x;
	int	y;
}	t_loc;

char		*scan_file(char *filename);
void		init_gameinfo(t_gameinfo *gameinfo, char *filename);
void		check_map(t_gameinfo *gameinfo);
int			correct_extension(char *check, char *end);
int			is_valid(char c);
void		exit_with_message(char *message);
void		draw_square(mlx_image_t *img, t_loc loc, int size, int color);
void		draw_image(t_gameinfo *gameinfo);

#endif
