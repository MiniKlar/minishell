/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:14:40 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/24 17:52:40 by lpatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	calcul_len_tokens(t_token *tokens)
{
	size_t	i;

	i = 0;
	if (!tokens)
		return (0);
	while (tokens)
	{
		if (ft_strncmp(tokens->value, "|", 2) == 0)
			break ;
		else if (is_redirection(tokens) > 0)
			tokens = tokens->next;
		else
			i++;
		tokens = tokens->next;
	}
	return (i);
}

static void	fill_cmd(t_shell **shell, t_token *tokens)
{
	int		i;
	int		len_array;
	char	**array;

	if (!tokens)
		return ;
	else
	{
		i = -1;
		len_array = calcul_len_tokens(tokens);
		array = malloc(sizeof(char *) * (len_array + 1));
		if (!array || len_array == 0)
			return (free(array));
		array[len_array] = 0;
		while (++i <= len_array - 1 && tokens)
		{
			if (is_redirection(tokens) > 0 || ft_strncmp(tokens->value, "|", 2)
				== 0)
				tokens = tokens->next;
			if (tokens)
				array[i] = ft_strdup(tokens->value);
			tokens = tokens->next;
		}
		(*shell)->cmd->cmd = array;
	}
}

static void	forward_tokens(t_token **tokens, int *index, int *i)
{
	while (*index != *i)
	{
		if ((*tokens) != NULL)
			(*tokens) = (*tokens)->next;
		*index += 1;
	}
}

static void	next_tokens(t_token **tokens, int i)
{
	int	index;

	index = 0;
	if (!tokens)
		return ;
	if (i == 1)
		*tokens = (*tokens)->next;
	else if (i == 2)
		forward_tokens(tokens, &index, &i);
	else
	{
		while (*tokens)
		{
			if (is_redirection((*tokens)) > 0
				|| ft_strncmp((*tokens)->value, "|", 2) == 0)
				break ;
			else
				*tokens = (*tokens)->next;
		}
	}
}

int	process_token(t_shell **shell, t_token *tokens)
{
	t_cmd	*tmp;

	tmp = (*shell)->cmd;
	while (tokens != NULL)
	{
		if (ft_strncmp(tokens->value, "|", 2) == 0)
		{
			(*shell)->nb_pipe++;
			(*shell)->cmd->next = init_cmd(NULL);
			(*shell)->cmd = (*shell)->cmd->next;
			next_tokens(&tokens, 1);
		}
		else if (is_redirection(tokens) > 0)
		{
			handle_redirection_token(tokens, (*shell)->cmd);
			next_tokens(&tokens, 2);
		}
		else
		{
			fill_cmd(shell, tokens);
			next_tokens(&tokens, 0);
		}
	}
	(*shell)->cmd = tmp;
	return (0);
}
