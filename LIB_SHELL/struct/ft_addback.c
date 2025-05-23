/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addback.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:22:57 by lomont            #+#    #+#             */
/*   Updated: 2025/05/22 19:18:09 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

void	token_add_back(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	redir_add_back(t_redir **head, t_redir *new)
{
	t_redir	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	cmd_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_cmd	*add_cmd_to_shell(t_shell *shell, char **cmd_args)
{
	t_cmd	*new_cmd;

	if (!shell || !cmd_args)
		return (NULL);
	new_cmd = init_cmd(cmd_args);
	if (!new_cmd)
		return (NULL);
	cmd_add_back(&(shell->cmd), new_cmd);
	shell->nb_pipe = get_cmd_count(shell->cmd) - 1;
	return (new_cmd);
}

bool	add_redir_to_cmd(t_cmd *cmd, char *str, t_symbol symbol)
{
	t_redir	*new_redir;

	if (!cmd || !str)
		return (false);
	new_redir = init_redir(str, symbol);
	if (!new_redir)
		return (false);
	redir_add_back(&(cmd->redir), new_redir);
	return (true);
}
