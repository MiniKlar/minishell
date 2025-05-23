/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 01:36:50 by lomont            #+#    #+#             */
/*   Updated: 2025/05/22 16:43:32 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

int	format_handler(va_list ptr, char str)
{
	int	counter;

	counter = 0;
	if (str == 'c')
		counter += ft_print_char(va_arg(ptr, int));
	else if (str == 's')
		counter += ft_print_str(va_arg(ptr, char *));
	else if (str == 'p')
		counter += ft_print_hexaptr(va_arg(ptr, void *));
	else if (str == 'd')
		counter += ft_print_nbr(va_arg(ptr, long int));
	else if (str == 'i')
		counter += ft_print_nbr(va_arg(ptr, long int));
	else if (str == 'u')
		counter += ft_put_unsigned(va_arg(ptr, unsigned int));
	else if (str == 'x')
		counter += ft_puthexa_lower(va_arg(ptr, int));
	else if (str == 'X')
		counter += ft_puthexa_upper(va_arg(ptr, int));
	else if (str == '%')
		counter += ft_print_char('%');
	return (counter);
}

int	ft_printf(const char *string, ...)
{
	int		i;
	int		counter;
	va_list	ptr;

	counter = 0;
	i = 0;
	va_start(ptr, string);
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			counter += format_handler(ptr, string[i + 1]);
			i++;
		}
		else
		{
			write(1, &string[i], 1);
			counter++;
		}
		i++;
	}
	va_end(ptr);
	return (counter);
}
