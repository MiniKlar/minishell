/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:23:25 by miniklar          #+#    #+#             */
/*   Updated: 2025/05/22 16:44:42 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*int main(void)
{
	printf("%d %d\n", ft_strncmp("salut", "salzt", 3);
	printf("%d %d\n", ft_strncmp("salut", "bonjour", 5);
	printf("%d %d\n", ft_strncmp("Hello", "sazut", 6);
	printf("%d %d\n", ft_strncmp("", "test", 1);
	printf("%d %d\n", ft_strncmp("test", "", 2);
	printf("%d %d\n", ft_strncmp("", "1", 1);
	printf("%d %d\n", ft_strncmp("abcdef", "abc\375xx", 5);
	printf("%d %d\n", ft_strncmp("", "test", 4);
}*/
