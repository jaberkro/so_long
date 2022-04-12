/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scan_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 12:42:18 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/12 15:54:30 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

static char	*read_join(int fd, char *output)
{	
	char	buf[4096];
	int		bytes_read;
	char	*old_output;

	while (42)
	{
		bytes_read = read(fd, buf, sizeof(buf) - 1);
		if (bytes_read < 0)
		{
			free(output);
			return (NULL);
		}
		if (!bytes_read)
			break ;
		buf[bytes_read] = '\0';
		old_output = output;
		output = ft_strjoin(output, buf);
		if (output == NULL)
			return (NULL);
		free(old_output);
	}
	return (output);
}

char	*scan_file(char	*filename)
{
	char	*output;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	output = ft_strdup("");
	if (!output)
		return (NULL);
	output = read_join(fd, output);
	if (!output)
		return (NULL);
	close(fd);
	return (output);
}
