/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 01:01:48 by lomont            #+#    #+#             */
/*   Updated: 2025/05/22 16:43:26 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

int	ft_print_str(char *s)
{
	int	counter;

	counter = 0;
	if (!s)
	{
		write (1, "(null)", 6);
		return (counter += 6);
	}
	while (*s)
	{
		write(1, &*s, 1);
		s++;
		counter++;
	}
	return (counter);
}
