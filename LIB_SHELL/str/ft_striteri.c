/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:44:39 by miniklar          #+#    #+#             */
/*   Updated: 2025/05/22 16:44:27 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

// void    ft_tolower1(unsigned int n, char *s)
// {
// 	if (*s >= 65 && *s <= 90)
// 		*s = *s + n;
// }
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
// int main(void)
// {
//     char s[5] = "SALUT";
//     ft_striteri(s, (ft_tolower1));
//     printf("%s\n", s);
// }
