/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/04 16:52:27 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/09 18:08:51 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**read_split(char *filename)
{
	char	*input;
	char	**splitted;

	input = scan_file(filename);
	if (input == NULL)
		exit_with_message("Error\nInvalid file");
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
	if (gameinfo->width < 30 && gameinfo->height < 30)
		gameinfo->size = 100;
	else if (gameinfo->width < 60 && gameinfo->height < 60)
		gameinfo->size = 50;
	else
		gameinfo->size = 25;
}
