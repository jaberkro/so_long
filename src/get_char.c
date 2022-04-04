/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_char.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 19:23:15 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/04/04 14:35:46 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

char	get_char(int fd)
{
	char	buf[1];
	int		bytes_read;

	bytes_read = read(fd, buf, 1);
	if (bytes_read <= 0)
		return (0);
	return (buf[0]);
}
