/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 15:25:29 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/13 13:58:48 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid(char c)
{
	if (c == '0' || c == '1' || c == 'P' || c == 'C' || c == 'E')
		return (1);
	return (0);
}

void	exit_with_message(char *message)
{
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
}

int	correct_extension(char *check, char *end)
{
	int	checklen;
	int	endlen;

	checklen = ft_strlen(check);
	endlen = ft_strlen(end);
	return (ft_strncmp(check + checklen - endlen, end, endlen));
}

void	check_char(t_data *data, int i, int j)
{
	if (is_valid(data->map[i][j]) == 0)
		exit_with_message("Error\nMap has invalid char");
	if ((i == 0 || i == data->height - 1 || j == 0 || \
		j == data->width - 1) && data->map[i][j] != '1')
		exit_with_message("Error\nMap has incomplete borders");
	if (data->map[i][j] == 'P' && data->map_loc.x == 0)
	{
		data->p_count++;
		data->map_loc.x = j;
		data->map_loc.y = i;
	}
	else if (data->map[i][j] == 'P')
		data->map[i][j] = '0';
	else if (data->map[i][j] == 'C')
		data->c_count++;
	else if (data->map[i][j] == 'E' && data->e_count == 0)
		data->e_count++;
	else if (data->map[i][j] == 'E')
		data->map[i][j] = '0';
}

void	check_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height)
	{
		j = 0;
		if (ft_strlen(data->map[i]) != (size_t)data->width)
			exit_with_message("Error\nMap is not rectangle");
		while (j < data->width)
		{
			check_char(data, i, j);
			j++;
		}
		i++;
	}
	if (data->p_count == 0)
		exit_with_message("Error\nNo player starting position");
	if (data->e_count == 0)
		exit_with_message("Error\nAmount of exits is 0");
	if (data->c_count == 0)
		exit_with_message("Error\nAmount of collectibles is 0");
}
