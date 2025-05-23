/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:12:03 by miniklar          #+#    #+#             */
/*   Updated: 2025/05/22 16:44:39 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*new_s;

	i = 0;
	new_s = malloc((sizeof(char) * ft_strlen(s)) + 1);
	if (!new_s)
		return (NULL);
	while (s[i] != '\0')
	{
		new_s[i] = f(i, s[i]);
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
/*int main(void)
{
	char *s = "SALUT";

	s = ft_strmapi(s, ft_tolower1);
	printf("%s\n", s);
}*/

/*char    ft_tolower1(unsigned int n, char c)
{
	if (c >= 65 && c <= 90)
	{
		return (c + n);
	}
	else
		return (0);

}*/
