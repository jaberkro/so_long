/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 15:14:21 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/03/31 15:26:33 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

char	**read_split(int fd, int *width, int *height)
{
	char	*input;
	char	**splitted;

	*height = 0;
	input = scan_file(fd);
	splitted = ft_split(input, '\n');
	if (!splitted)
	{
		free(input);
		return (NULL);
	}
	while (splitted[*height])
		(*height)++;
	*width = ft_strlen(splitted[0]);
	return (splitted);
}

t_map	*init_map(int fd)
{
	char	**map_values;
	t_map	*new_map;
	int		width;
	int		height;
	
	map_values = read_split(fd, &width, &height);
	new_map = malloc(sizeof(t_map));
	if (!new_map)
		return (NULL);
	new_map->p_count = 0;
	new_map->c_count = 0;
	new_map->e_count = 0;
	new_map->width = width;
	new_map->height = height;
	new_map->map = map_values;
	if (error_check(new_map) == 0)
	{
		free(map_values);
		free(new_map);
		return (NULL);
	}
	return (new_map);
}


// int	find_width_height(int fd, size_t *width, size_t *height)
// {
// 	char	*s;
	
// 	s = get_next_line(fd);
// 	*width = ft_strlen(s);
// 	*height = 0;
// 	while (s != NULL)
// 	{
// 		s = get_next_line(fd);
// 		(*height)++;
// 		if (s == NULL)
// 			break ;
// 		else if (ft_strlen(s) != *width && ft_strlen(s) != *width - 1)
// 		{
// 			ft_printf("Error\nMap is not rectangle\n");
// 			return (0);
// 		}
// 	}
// 	return (1);
// }

// t_map	*init_map(int fd)
// {
// 	t_map	*map;
// 	size_t	width;
// 	size_t	height;
// 	size_t	i;

// 	i = 0;
// 	if (find_width_height(fd, &width, &height) == 0)
// 		return (NULL);
// 	map->width = width;
// 	map->height = height;
// 	map->map = malloc((height + 1) * sizeof(char *));
// 	if (map->map == NULL)
// 		return (NULL);
// 	while (i < height)
// 	{
// 		map->map[i] = malloc(width * sizeof(char));
// 		if (map->map[i] == NULL)
// 			return (NULL);
// 		i++;
// 	}
// 	ft_printf("width:%d, height:%d\n", width, height);
// 	return (map);
// }


// void	print_map(char map[1000][1000])
// {
// 	int	i;
// 	int	j;

// 	j = 0;
// 	i = 0;
// 	while (map[j][i])
// 	{
// 		i = 0;
// 		if (map[j][i] == '\0')
// 			break ;
// 		while (map[j][i])
// 		{
// 			if (map[j][i] == '\0')
// 				break ;
// 			ft_printf("%c", map[j][i]);
// 			i++;
// 		}
// 		ft_printf("\n");
// 		j++;
// 	}
// 	ft_printf("\n");
// }

// int	parsing(int fd)
// {
// 	char	c;
// 	int		i;
// 	int		j;
// 	char	**map;

// 	c = 's';
// 	j = 0;
// 	i = 0;
// 	while (c != 0)
// 	{
// 		c = get_char(fd);
// 		map[j][i] = c;
// 		if (c == '\n' || c == 0)
// 		{
// 			map[j][i] = '\0';
// 			j++;
// 			if (c == 0)
// 			{
// 				ft_printf("width:%d, height:%d\n", i, j);
// 				break ;
// 			}
// 			i = 0;
// 		}
// 		else if (is_valid(c) == 0)
// 		{
// 			ft_printf("\nError\nInvalid char in map: %c\n", c);
// 			return (0);
// 		}
// 		if (c != 0)
// 			ft_printf("%c", c);
// 		i++;
// 	}
// 	ft_printf("\n");
// 	//print_map(map);
// 	return (1);
// }

// t_map	*init_map(int fd)
// {
// 	// size_t	height;
// 	// size_t	width;
// 	// t_map	*map;
// 	// t_list	*list;

// 	// list = NULL;
// 	// init_list(fd &width, &height, &list);
// 	// if (map_width_height(fd, &width, &height) == 0)
// 	// 	ft_printf("Error\n map not a rectangle\n");
// 	// map = fill_map(fd, width, height);
// 	// if (map == NULL)
// 	// 	ft_printf("Error\n map not valid\n");
// 	// ft_printf("height: %d tiles. width: %d tiles\n", height, width);
// 	// return (map);
// }

/*

- read and check everything
- convert to 2D array

*/