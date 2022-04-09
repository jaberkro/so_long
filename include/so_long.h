/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 15:13:28 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/09 14:13:53 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "MLX42.h"
# include "libft.h"

typedef struct s_player{
	int	px;
	int	py;
	int	moves;
	int	c_found;
}	t_player;

typedef struct s_gameinfo{
	int			w;
	int			h;
	int			size;
	char		**map;
	t_player	player;
	int			p;
	int			c;
	int			e;
	mlx_image_t	*img;
	mlx_t		*mlx;
}	t_gameinfo;

typedef struct s_loc{
	int	x;
	int	y;
}	t_loc;

t_gameinfo	init_gameinfo(t_gameinfo *gameinfo, int fd);
t_player	init_player(void);
int			correct_extension(char *check, char *end);
int			is_valid(char c);
char		*scan_file(int fd);
int			check_map(t_gameinfo *gameinfo);
int			error_message(char *message);
t_gameinfo	free_return_map(t_gameinfo *to_free);
void		draw_square(mlx_image_t *img, t_loc loc, int size, int color);
void		draw_image(t_gameinfo *gameinfo);

#endif
