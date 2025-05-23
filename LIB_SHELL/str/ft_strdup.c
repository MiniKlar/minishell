/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:29:13 by lomont            #+#    #+#             */
/*   Updated: 2025/05/22 16:44:23 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

char	*ft_strdup(const char *s)
{
	char	*tmp;
	size_t	srclen;

	srclen = ft_strlen(s) + 1;
	tmp = malloc(srclen * sizeof(char));
	if (!tmp)
		return (NULL);
	ft_memmove(tmp, s, srclen);
	return (tmp);
}
// int	main(void)
// {
// 	char	*str = "sadfvbf";
// 	char	*tmp;

// 	tmp = ft_strdup(str);
// 	printf("%s\n", str);
// 	printf("%s\n", tmp);
// 	tmp = strdup(str);
// 	printf("%s\n", tmp);
// }
