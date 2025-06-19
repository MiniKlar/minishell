/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:28:32 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/15 23:08:17 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_useruid(char *user_uid, int fd)
{
	char	*str;
	char	*tmp;

	str = get_next_line(fd);
	if (!str)
		return (NULL);
	while (str)
	{
		if (!str)
		return (NULL);
		if (ft_strnstr(str, user_uid, ft_strlen(str)) == 0)
			continue;
		else
			break;
		str = get_next_line(fd);
	}
	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
	return (str);
}

static char *get_useruid(void)
{
	char		*user_uid;
	char		*terminal_name;
	char		*tmp;
	struct stat	ttystat;

	terminal_name = ttyname(0);
	if (stat(terminal_name, &ttystat) == -1)
	{
		perror("stat");
		return (NULL);
	}
	else
	{
		user_uid = ft_itoa(ttystat.st_uid);
		tmp = user_uid;
		user_uid = ft_strjoin(":", user_uid);
		free(tmp);
		tmp = user_uid;
		user_uid = ft_strjoin(user_uid, ":");
		free(tmp);
		return(user_uid);
	}
}

static void		fill_index(char *str, size_t *i, size_t *k, size_t *j)
{
	while (str[*i])
	{
		if (str[*i] == ':')
		{
			*k += 1;
			if (*k == 5)
				*j = *i + 1;
			if (*k == 6)
				break;
		}
		*i += 1;
	}
}

static char 	*find_home(char *str)
{
	char	*tmp;
	size_t	i;
	size_t	k;
	size_t	j;

	i = 0;
	k = 0;
	j = 0;
	fill_index(str, &i, &k, &j);
	if (k == 6)
	{
		tmp = str;
		str = ft_substr(str, j, i - j);
		free(tmp);
		return (str);
	}
	else
		return (NULL);
}

char	*gethome_without_env(void)
{
	char		*user_uid;
	char		*str;
	int			fd;

	user_uid = get_useruid();
	if (!user_uid)
		return (NULL);
	fd = open("/etc/passwd", O_RDONLY);
	if (fd == -1)
		perror("open");
	else
	{
		str = search_useruid(user_uid, fd);
		free(user_uid);
		close (fd);
		if (!str)
			return (NULL);
		else
			return (find_home(str));
	}
	return (NULL);
}
