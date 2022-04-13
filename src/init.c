/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/04 16:52:27 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/13 14:19:30 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_mlx_and_images(t_data *data)
{
	int	mlx_width;
	int	mlx_height;
	int	xs_size;

	mlx_width = data->width * data->size;
	mlx_height = data->height * data->size;
	xs_size = data->size * 0.8;
	data->mlx = mlx_init(mlx_width, mlx_height, "SO_LONG", true);
	if (!data->mlx)
		exit_with_message("Error\nCreating mlx failed");
	data->img = mlx_new_image(data->mlx, mlx_width, mlx_height);
	data->p_img = mlx_new_image(data->mlx, xs_size, xs_size);
	if (!data->img || !data->p_img)
		exit_with_message("Error\nCreating new image failed");
}

int	consecutive_newline(char *input)
{
	char	last;
	int		i;

	i = 0;
	last = '\n';
	while (input[i])
	{
		if (input[i] == last && input[i] == '\n')
			return (1);
		last = input[i];
		i++;
	}
	return (0);
}

char	**read_split(char *filename)
{
	char	*input;
	char	**splitted;

	input = scan_file(filename);
	if (ft_strncmp(input, "", 1) == 0)
		exit_with_message("Error\nEmpty file");
	if (consecutive_newline(input))
		exit_with_message("Error\nConsecutive newline");;
	splitted = ft_split(input, '\n');
	free(input);
	if (!splitted)
		exit_with_message("Error\nMalloc failed");
	if (!splitted[0])
		exit_with_message("Error\nFile only contains newline");
	return (splitted);
}

void	set_zero(t_data *data)
{
	data->height = 0;
	data->p_count = 0;
	data->c_count = 0;
	data->e_count = 0;
	data->c_found = 0;
	data->moves = 0;
	ft_bzero(&data->map_loc, sizeof(t_loc));
	ft_bzero(&data->img_loc, sizeof(t_loc));
}

void	init_data(t_data *data, char *filename)
{
	int	width_size;
	int	height_size;

	set_zero(data);
	data->map = read_split(filename);
	while (data->map[data->height])
		data->height++;
	data->width = ft_strlen(data->map[0]);
	check_map(data);
	width_size = 4500 / data->width * 0.55 / 10 * 10;
	height_size = 2250 / data->height * 0.55 / 10 * 10;
	if (width_size < height_size)
		data->size = width_size;
	else
		data->size = height_size;
	data->img_loc.x = data->map_loc.x * data->size + data->size * 0.1;
	data->img_loc.y = data->map_loc.y * data->size + data->size * 0.1;
}
