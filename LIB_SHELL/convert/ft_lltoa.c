/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:19:05 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/24 17:34:36 by lpatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

static int	count_digit(long long n)
{
	int	counter;

	counter = 0;
	if (n < 0)
		n = -n;
	if (n == 0)
		counter++;
	while (n != 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

char	*ft_lltoa(long long n)
{
	char		*str;
	size_t		len_n;
	size_t		i;
	int			neg;
	long long	n1;

	n1 = n;
	neg = ft_isnegative(n1);
	len_n = count_digit(n1) + neg;
	str = malloc(sizeof(char) * (len_n + 1));
	if (!str)
		return (NULL);
	i = len_n;
	if (neg == 1)
		n1 = n1 * -1;
	while (i-- != 0)
	{
		str[i] = (n1 % 10) + '0';
		n1 /= 10;
	}
	if (neg == 1)
		str[0] = '-';
	str[len_n] = 0;
	return (str);
}
