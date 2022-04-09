/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 15:25:29 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/09 18:13:03 by jaberkro      ########   odam.nl         */
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

void	check_char(t_gameinfo *ginfo, int i, int j)
{
	if (is_valid(ginfo->map[i][j]) == 0)
		exit_with_message("Error\nMap has invalid char");
	if ((i == 0 || i == ginfo->height - 1 || j == 0 || \
		j == ginfo->width - 1) && ginfo->map[i][j] != '1')
		exit_with_message("Error\nMap has incomplete borders");
	if (ginfo->map[i][j] == 'P' && ginfo->player.posx == 0)
	{
		ginfo->p_count++;
		ginfo->player.posx = j;
		ginfo->player.posy = i;
	}
	else if (ginfo->map[i][j] == 'P')
		ginfo->map[i][j] = '0';
	else if (ginfo->map[i][j] == 'C')
		ginfo->c_count++;
	else if (ginfo->map[i][j] == 'E' && ginfo->e_count == 0)
		ginfo->e_count++;
	else if (ginfo->map[i][j] == 'E')
		ginfo->map[i][j] = '0';
}

void	check_map(t_gameinfo *ginfo)
{
	int	i;
	int	j;

	i = 0;
	while (i < ginfo->height)
	{
		j = 0;
		if (ft_strlen(ginfo->map[i]) != (size_t)ginfo->width)
			exit_with_message("Error\nMap is not rectangle");
		while (j < ginfo->width)
		{
			check_char(ginfo, i, j);
			j++;
		}
		i++;
	}
	if (ginfo->p_count == 0)
		exit_with_message("Error\nNo player starting position");
	if (ginfo->e_count == 0)
		exit_with_message("Error\nAmount of exits is 0");
	if (ginfo->c_count == 0)
		exit_with_message("Error\nAmount of collectibles is 0");
}
