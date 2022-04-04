/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 15:25:29 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/04 18:13:08 by jaberkro      ########   odam.nl         */
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

int	check_char(t_gameinfo *ginfo, int i, int j)
{
	if (is_valid((*ginfo).map[i][j]) == 0)
		return (error_message("Error\nMap has invalid char"));
	if ((i == 0 || i == (*ginfo).h - 1 || j == 0 || \
		j == (*ginfo).w - 1) && (*ginfo).map[i][j] != '1')
		return (error_message("Error\nMap has incomplete borders"));
	if ((*ginfo).map[i][j] == 'P')
	{
		(*ginfo).p++;
		(*ginfo).player.px = j;
		(*ginfo).player.py = i;
	}
	else if ((*ginfo).map[i][j] == 'C')
		(*ginfo).c++;
	else if ((*ginfo).map[i][j] == 'E')
		(*ginfo).e++;
	return (1);
}

int	check_map(t_gameinfo *ginfo)
{
	int	i;
	int	j;

	i = 0;
	while (i < (*ginfo).h)
	{
		j = 0;
		if (ft_strlen((*ginfo).map[i]) != (size_t)(*ginfo).w)
			return (error_message("Error\nMap is not rectangle"));
		while (j < (*ginfo).w)
		{
			if (check_char(ginfo, i, j) == 0)
				return (0);
			j++;
		}
		i++;
	}
	if ((*ginfo).p == 0)
		return (error_message("Error\nNo player starting position"));
	if ((*ginfo).e == 0)
		return (error_message("Error\nAmount of exits is 0"));
	if ((*ginfo).c == 0)
		return (error_message("Error\nAmount of collectibles is 0"));
	return (1);
}
