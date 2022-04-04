/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/04 16:52:27 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/04 22:13:35 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_gameinfo	free_return_map(t_gameinfo *to_free)
{
	int	i;

	i = 0;
	while (to_free->map[i])
	{
		free(to_free->map[i]);
		i++;
	}
	free(to_free->map);
	return (*to_free);
}

char	**read_split(int fd, int *width, int *height)
{
	char	*input;
	char	**splitted;

	*height = 0;
	input = scan_file(fd);
	splitted = ft_split(input, '\n');
	free(input);
	if (!splitted)
		return (NULL);
	while (splitted[*height])
		(*height)++;
	*width = ft_strlen(splitted[0]);
	return (splitted);
}

t_player	init_player(void)
{
	t_player	new_player;

	new_player.px = 0;
	new_player.py = 0;
	new_player.c_found = 0;
	new_player.moves = 0;
	return (new_player);
}

t_gameinfo	init_gameinfo(t_gameinfo *gameinfo, int fd)
{
	gameinfo->player = init_player();
	gameinfo->map = read_split(fd, &gameinfo->w, &gameinfo->h);
	if (!gameinfo->map)
		return (*gameinfo);
	gameinfo->p = 0;
	gameinfo->c = 0;
	gameinfo->e = 0;
	if (check_map(gameinfo) == 0)
		return (free_return_map(gameinfo));
	if (gameinfo->w < 30 && gameinfo->h < 30)
		gameinfo->size = 100;
	else if (gameinfo->w < 60 && gameinfo->h < 60)
		gameinfo->size = 50;
	else
		gameinfo->size = 25;
	return (*gameinfo);
}
