/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 01:00:48 by lomont            #+#    #+#             */
/*   Updated: 2025/05/22 16:43:24 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

int	ft_print_nbr(int n)
{
	int	counter;

	counter = 0;
	if (n == -2147483648)
	{
		return (ft_print_str("-2147483648"));
	}
	if (n < 0)
	{
		counter += ft_print_char('-');
		n = -n;
	}
	if (n >= 10)
	{
		counter += ft_print_nbr(n / 10);
		counter += ft_print_char((n % 10) + '0');
	}
	else
	{
		counter += ft_print_char(n + '0');
	}
	return (counter);
}
