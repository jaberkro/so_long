/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 15:13:28 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/04 18:33:21 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "MLX42.h"
# include "libft.h"

typedef	struct	s_player{
	int	px;
	int	py;
	int	moves;
	int c_found;
}	t_player;

typedef	struct s_gameinfo{
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


t_gameinfo	init_gameinfo(t_gameinfo *gameinfo, int fd);
t_player	init_player(void);
int	check_map(t_gameinfo *gameinfo);

void	print_map(char **map);





char	*scan_file(int fd);
//t_map	*init_map(int fd);
//int		error_check(t_map *this_map);


void	draw_square(mlx_image_t* img, float x, float y, int size, int color);
void	draw_background(t_gameinfo *gameinfo);


char	get_char(int fd);

#endif


// typedef struct s_player{
// 	int		px;
// 	int		py;
// 	int		c_found;
// 	int		movements;
// }		t_player;

// typedef struct s_map{
// 	int			w;
// 	int 		h;
// 	char		**map;
// 	int			sqw;
// 	int			sqh;
// 	int			p_count;
// 	int			e_count;
// 	int			c_count;
// }       t_map;

// typedef struct s_gameinfo{
// 	t_map		*map;
// 	t_player	*player;
// 	mlx_image_t	*img;
// 	mlx_t		*mlx;
// }			t_gameinfo;