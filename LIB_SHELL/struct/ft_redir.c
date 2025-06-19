/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:04:59 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/17 01:23:49 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

t_redir	*create_node_here_redir(char *arg)
{
	t_redir	*shell;

	shell = malloc(sizeof(t_redir));
	if (!shell)
		return (NULL);
	shell->str = ft_strdup(arg);
	shell->symbol = HERE_DOC;
	shell->next = NULL;
	return (shell);
}

t_redir	*create_node_redir(char *arg)
{
	t_redir	*shell;

	shell = malloc(sizeof(t_redir));
	if (!shell)
		return (NULL);
	shell->str = ft_strdup(arg);
	shell->symbol = REDIR_IN;
	shell->next = NULL;
	return (shell);
}

t_redir	*create_node_redir_out(char *arg)
{
	t_redir	*shell;

	shell = malloc(sizeof(t_redir));
	if (!shell)
		return (NULL);
	shell->str = ft_strdup(arg);
	shell->symbol = REDIR_OUT;
	shell->next = NULL;
	return (shell);
}
