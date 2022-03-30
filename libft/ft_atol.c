/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 13:46:53 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/02/25 13:48:21 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	int		sign;
	long	out;
	long	counter;

	sign = 1;
	out = 0;
	counter = 0;
	while (ft_isspace(str[counter]))
		counter++;
	if (str[counter] == '-' || str[counter] == '+')
	{
		if (str[counter] == '-')
			sign = -1;
		counter++;
	}
	while (ft_isdigit(str[counter]))
	{
		out = out * 10 + str[counter] - 48;
		counter++;
	}
	return (out * sign);
}

/* The atol() function converts the initial portion of the string pointed to
     by str to long representation.
 */