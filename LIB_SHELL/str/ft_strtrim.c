/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:50:14 by lomont            #+#    #+#             */
/*   Updated: 2025/05/22 16:44:51 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i - 1]))
		i--;
	return (ft_substr(s1, 0, i));
}
// int	main(void)
// {
// 	char	*tmp;

// 	tmp = ft_strtrim("zzzbabzaaaFE!Nzzab", "zab");
// 	printf("%s\n", tmp);
// }
