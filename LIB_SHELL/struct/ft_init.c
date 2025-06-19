/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:25:30 by lomont            #+#    #+#             */
/*   Updated: 2025/06/19 02:26:55 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		ft_putstr_fd("Error allocation shell struct!", 2);
		exit(EXIT_FAILURE);
	}
	shell->envp = ft_malloc_envp(envp);
	shell->cmd = NULL;
	shell->id_fork = NULL;
	shell->pipex = NULL;
	shell->nb_pipe = 0;
	shell->exit_code = 0;
	shell->is_child = false;
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->tmp_stdin = -1;
	shell->tmp_stdout = -1;
	return (shell);
}

t_token	*init_token(char *value)
{
	t_token	*new;

	if (!value)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_redir	*init_redir(char *str, t_symbol symbol)
{
	t_redir	*new;

	if (!str)
		return (NULL);
	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->symbol = symbol;
	new->str = ft_strdup(str);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_cmd	*init_cmd(char **cmd_args)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = cmd_args;
	new->redir = NULL;
	new->next = NULL;
	return (new);
}
