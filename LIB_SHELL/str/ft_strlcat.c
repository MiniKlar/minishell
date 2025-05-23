/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:14:03 by miniklar          #+#    #+#             */
/*   Updated: 2025/05/22 16:44:32 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)

{
	size_t	srclen;
	size_t	dstlen;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstlen >= size)
		dstlen = size;
	if (dstlen == size)
		return (srclen + size);
	if (srclen < size - dstlen)
		ft_memcpy(dst + dstlen, src, srclen + 1);
	else
	{
		ft_memcpy(dst + dstlen, src, size - dstlen - 1);
		dst[size - 1] = '\0';
	}
	return (srclen + dstlen);
}

/*int main(void)
{
	char dst[100] = "0123456";
	char src[100] = "abcdefg";

	ft_strlcat(dst, src, 20);
	printf("%s \n", dst);
	return (0);
}*/
