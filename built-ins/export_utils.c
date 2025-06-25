/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:11:27 by lpatin            #+#    #+#             */
/*   Updated: 2025/06/25 11:20:43 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_char_arg(char *arg)
{
	char	*new_arg;
	size_t	i;

	i = 0;
	new_arg = malloc(sizeof(char) * (ft_strlen(arg)));
	if (!new_arg)
		return (NULL);
	while (arg[i] != '=')
		i++;
	ft_memmove(new_arg, arg, i - 1);
	ft_memmove(new_arg + i - 1, arg + i, ft_strlen(arg) - i);
	new_arg[ft_strlen(arg) - 1] = '\0';
	return (new_arg);
}

char	*remove_extra_char_before_egal(char *arg)
{
	size_t	i;
	bool	remove_char;

	i = 0;
	remove_char = false;
	while (arg[i] != '\0')
	{
		if (arg[i + 1] == '=' && (arg[i] == '+'
				|| arg[i] == '_' || arg[i] == '<' || arg[i] == '>'))
			remove_char = true;
		i++;
	}
	if (remove_char == true)
		return (remove_char_arg(arg));
	return (ft_strdup(arg));
}

bool	check_arg_export_syntax(char *arg)
{
	size_t	i;
	bool	egal_seen;

	i = 0;
	egal_seen = true;
	if ((!ft_isalpha(arg[0]) && arg[0] != '_') || arg[0] == '\0')
		return (error_export(arg, 0));
	while (arg[++i])
	{
		if (arg[i] == '=')
		{
			egal_seen = true;
			break ;
		}
		if (ft_isalnum(arg[i]) != true && arg[i + 1] != '=' && arg[i]
			!= '_')
			return (error_export(arg, 0));
		else if (ft_isalnum(arg[i]) != true && arg[i + 1] == '=' && arg[i]
			!= '+' && arg[i] != '_' && arg[i] != '<' && arg[i] != '>')
			return (error_export(arg, 0));
	}
	if (egal_seen)
		return (true);
	return (false);
}

bool	error_export(char *arg, int error_code)
{
	if (error_code == 1)
	{
		ft_putstr_fd("bash: export: ", 2);
		ft_putchar_fd(arg[0], 2);
		ft_putchar_fd(arg[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
	}
	else
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	return (false);
}

void	export_all(char **envp)
{
	size_t	i;
	size_t	k;
	size_t	index_egal;

	i = 0;
	while (envp[i])
	{
		k = -1;
		index_egal = 0;
		ft_putstr_fd("export ", 1);
		while (envp[i][++k])
		{
			if (k > 0)
				if (envp[i][k - 1] == '=')
					ft_putchar_fd('"', 1);
			if (envp[i][k] == '=')
				index_egal = k;
			ft_putchar_fd(envp[i][k], 1);
		}
		if (envp[i][k] == '\0' && index_egal != k - 1 && index_egal != 0)
			ft_putstr_fd("\"\n", 1);
		else
			ft_putchar_fd('\n', 1);
		i++;
	}
}
