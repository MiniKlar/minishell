/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 02:31:54 by lomont            #+#    #+#             */
/*   Updated: 2025/05/22 16:42:55 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
/*int	main(void)
{
	printf("%d\n", ft_isdigit('0'));
	printf("%d\n", ft_isdigit('5'));
	printf("%d\n", ft_isdigit('9'));
	printf("%d\n", ft_isdigit('c'));
	printf("%d\n", ft_isdigit('\n'));
}*/
