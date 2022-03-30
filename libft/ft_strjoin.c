/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/22 20:59:15 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/02/26 16:21:59 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*out;
	size_t	i;

	i = 0;
	if (!s2 || ft_strncmp(s2, "", 1) == 0 || (!s2 && !s1))
		return (NULL);
	if (!s1)
		return ((char *)s2);
	len = ft_strlen(s1) + ft_strlen(s2);
	out = ft_calloc(len + 1, 1);
	if (out == NULL)
		return (NULL);
	while (i < len)
	{
		if (i < ft_strlen(s1))
			out[i] = s1[i];
		else
			out[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	return (out);
}

/* Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.

This function does not free s1, you have to handle that yourself.
 */