/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scan_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 12:42:18 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/04 14:37:10 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*scan_file(int fd)
{
	char	buf[4096];
	int		bytes_read;
	char	*output;
	char	*old_output;

	output = ft_strdup("");
	if (!output)
		return (NULL);
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
		free(old_output);
	}
	return (output);
}
