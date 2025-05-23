/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 00:04:35 by miniklar          #+#    #+#             */
/*   Updated: 2025/05/22 16:43:16 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
		ptr[i++] = (unsigned char) c;
	return (s);
}
/*int main(void)
{
	char    buffer[100] = "SALUT TU VQS VUEN AFWFWA";

	ft_memset(buffer, '7', 20);
	printf("%s\n", buffer);
}*/
