/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 15:25:29 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/03/31 17:43:29 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

static int	is_valid(char c)
{
	if (c == '0' || c == '1' || c == 'P' || c == 'C' || c == 'E')
		return (1);
	return (0);
}

static int	error_message(char *message)
{
	ft_printf("%s\n", message);
	return (0);
}

static int	error_check_char(t_map **this_map, int i, int j)
{
	if (is_valid((*this_map)->map[i][j]) == 0)
		return (error_message("Error\nMap has invalid char"));
	if ((i == 0 || i == (*this_map)->height - 1 || j == 0 || \
		j == (*this_map)->width - 1) && (*this_map)->map[i][j] != '1')
		return (error_message("Error\nMap has incomplete borders"));
	if ((*this_map)->map[i][j] == 'P')
	{
		((*this_map)->p_count)++;
		(*this_map)->px = j;
		(*this_map)->py = i;
	}
	else if ((*this_map)->map[i][j] == 'C')
		((*this_map)->c_count)++;
	else if ((*this_map)->map[i][j] == 'E')
		((*this_map)->e_count)++;
	return (1);
}

int	error_check(t_map *this_map)
{
	int	i;
	int	j;

	i = 0;
	while (i < this_map->height)
	{
		j = 0;
		if (ft_strlen(this_map->map[i]) != (size_t)this_map->width)
			return (error_message("Error\nMap is not rectangle")); 
		while (j < this_map->width)
		{
			if (error_check_char(&this_map, i, j) == 0)
				return (0);
			j++;
		}
		i++;
	}
	if (this_map->p_count == 0)
		return (error_message("Error\nAmount of player starting positions is 0"));
	if (this_map->e_count == 0)
		return (error_message("Error\nAmount of exits is 0"));
	if (this_map->c_count == 0)
		return (error_message("Error\nAmount of collectibles is 0"));
	return (1);
}
