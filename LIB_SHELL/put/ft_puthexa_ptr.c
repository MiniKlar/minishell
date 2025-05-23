/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 01:53:02 by lomont            #+#    #+#             */
/*   Updated: 2025/05/22 16:43:46 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

int	ft_puthexa_ptr(unsigned long address)
{
	char	*base16;
	int		counter;

	base16 = "0123456789abcdef";
	counter = 0;
	if (address >= 16)
		counter += ft_puthexa_ptr((address / 16));
	counter += ft_print_char(base16[address % 16]);
	return (counter);
}
