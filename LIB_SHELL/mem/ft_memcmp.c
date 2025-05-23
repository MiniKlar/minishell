/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:25:31 by miniklar          #+#    #+#             */
/*   Updated: 2025/05/22 16:43:10 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if ((unsigned char) p1[i] != (unsigned char) p2[i])
			return ((unsigned char) p1[i] - (unsigned char) p2[i]);
		i++;
	}
	return (0);
}
/*int main(void)
{
	printf("%d\n", memcmp("salut", "sazut", 5));
	printf("%d\n", memcmp("salut", "bonjour", 5));
	printf("%d\n", memcmp("Hello", "sazut", 6));
	printf("%d\n", memcmp("Hello", "Hello", 6));
	printf("%d\n", memcmp("salut", "toi", 0));
	printf("%d\n", memcmp("teste", "testex", 6));
	printf("%d\n", memcmp("abcdef", "abc\375xx", 6));
	printf("%d\n", memcmp("abc", "abc", 3));
	printf("%d\n", memcmp("abcdefghij", "abcdefgxyz", 7));
	printf("%d\n", memcmp("abcdefgh", "abcdzxyz", 7));
}*/
