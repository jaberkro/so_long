/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/04 16:52:27 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/12 18:13:20 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_mlx_and_images(t_gameinfo *gameinfo)
{
	int	mlx_width;
	int	mlx_height;
	int	xs_size;

	mlx_width = gameinfo->width * gameinfo->size;
	mlx_height = gameinfo->height * gameinfo->size;
	xs_size = gameinfo->size * 0.8;
	gameinfo->mlx = mlx_init(mlx_width, mlx_height, "SO_LONG", true);
	if (!gameinfo->mlx)
		exit_with_message("Error\nCreating mlx failed");
	gameinfo->img = mlx_new_image(gameinfo->mlx, mlx_width, mlx_height);
	gameinfo->player_img = mlx_new_image(gameinfo->mlx, xs_size, xs_size);
	if (!gameinfo->img || !gameinfo->player_img)
		exit_with_message("Error\nCreating new image failed");
}

char	**read_split(char *filename)
{
	char	*input;
	char	**splitted;

	input = scan_file(filename);
	if (input == NULL)
		exit_with_message("Error\nInvalid file or malloc failed");
	if (ft_strncmp(input, "", 1) == 0)
		exit_with_message("Error\nEmpty file");
	splitted = ft_split(input, '\n');
	free(input);
	if (!splitted)
		exit_with_message("Error\nMalloc failed");
	if (!splitted[0])
		exit_with_message("Error\nFile only contains newline");
	return (splitted);
}

void	init_gameinfo(t_gameinfo *gameinfo, char *filename)
{
	int	width_size;
	int	height_size;

	ft_bzero(&gameinfo->player, sizeof(t_player));
	ft_bzero(&gameinfo->height, sizeof(int));
	ft_bzero(&gameinfo->p_count, sizeof(int));
	ft_bzero(&gameinfo->c_count, sizeof(int));
	ft_bzero(&gameinfo->e_count, sizeof(int));
	gameinfo->map = read_split(filename);
	while (gameinfo->map[gameinfo->height])
		gameinfo->height++;
	gameinfo->width = ft_strlen(gameinfo->map[0]);
	check_map(gameinfo);
	width_size = 4500 / gameinfo->width * 0.55 / 10 * 10;
	height_size = 2250 / gameinfo->height * 0.55 / 10 * 10;
	if (width_size < height_size)
		gameinfo->size = width_size;
	else
		gameinfo->size = height_size;
}
