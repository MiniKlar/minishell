/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 23:45:57 by lomont            #+#    #+#             */
/*   Updated: 2025/05/22 16:42:45 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

char	*fill_line_buffer(char *left_c, int fd)
{
	char	*buffer;
	char	*temp;
	ssize_t	b_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (!left_c)
		left_c = ft_strdup("");
	if (!left_c)
		return (free(buffer), NULL);
	b_read = 1;
	while (b_read > 0 && !ft_strchr(left_c, '\n'))
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
			return (free(buffer), free(left_c), NULL);
		buffer[b_read] = '\0';
		temp = left_c;
		left_c = ft_strjoin(left_c, buffer);
		free(temp);
		if (!left_c)
			return (free(buffer), NULL);
	}
	return (free(buffer), left_c);
}

char	*set_line(char *line_buffer)
{
	char	*left_c;
	size_t	i;

	i = 0;
	if (!line_buffer[0])
		return (NULL);
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	left_c = ft_substr(line_buffer, 0, i + 1);
	return (left_c);
}

char	*set_left_c(char *line_buffer)
{
	char	*line;
	size_t	i;
	size_t	k;

	i = 0;
	k = ft_strlen(line_buffer);
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (!line_buffer[i])
		return (NULL);
	line = ft_substr(line_buffer, i + 1, k - i);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*left_c;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(left_c);
		left_c = NULL;
		return (NULL);
	}
	left_c = fill_line_buffer(left_c, fd);
	if (!left_c)
		return (NULL);
	line = set_line(left_c);
	if (!line)
	{
		free(left_c);
		left_c = NULL;
		return (NULL);
	}
	temp = left_c;
	left_c = set_left_c(left_c);
	free(temp);
	return (line);
}

char	*ft_strchr(const char *s, int c)
{
	if (*s == '\0')
		return (NULL);
	while (*s)
	{
		if (*s == (const char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (const char)c)
		return ((char *)s);
	else
		return (NULL);
}
