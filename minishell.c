/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:53:30 by lomont            #+#    #+#             */
/*   Updated: 2025/05/19 22:57:39 by lpatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *s_cmd_init(void)
{
	t_cmd *cmds;

	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	cmds->cmd = NULL;
	cmds->is_subshell = false;
	cmds->next = NULL;
	return (cmds);
}

t_shell	*p_init_shell_struct(void)
{
	t_shell	*lst;

	lst = malloc(sizeof(t_shell));
	if (!lst)
		return (NULL);
	lst->cmd = NULL;
	lst->redir = NULL;
	lst->nb_pipe = 0;
	lst->wstatus = 0;
	lst->tmp_name_heredoc = -1;
	lst->next = NULL;
	return (lst);
}

t_token *tokens_init(void)
{
	t_token *tokens;
	
	tokens = malloc(sizeof(t_token));
	if (!tokens)
		return (NULL);
	tokens->nb_tokens = 0;
	tokens->next = NULL;
	tokens->quote_type = NONE;
	tokens->value = NULL;
	return (tokens);
}

int main(void)
{
	t_token *tokens;
	t_token *tmp;
	t_cmd	*cmds;
	char	*str;
	int		nb;

	nb = 0;
	tokens = NULL;
	cmds = s_cmd_init();
	str = readline("mishinelle > ");
	ft_strtok(&tokens, str, cmds);
	tmp = tokens;
	while (tmp != NULL)
	{
		printf("Token: %s\n", tmp->value);
		tmp = tmp->next;
		nb++;
	}
	printf("Nb tokens: %d\n", nb);
	token_clear(&tokens);
	free(str);
	return (0);
}
