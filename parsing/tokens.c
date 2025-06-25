/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:14:40 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/25 00:57:54 by lomont           ###   ########.fr       */
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

static char	**fill_data(t_token *tokens, int *i, int *len_array)
{
	char	**array;

	*i = -1;
	*len_array = calcul_len_tokens(tokens);
	array = malloc(sizeof(char *) * (*len_array + 1));
	if (!array || len_array == 0)
	{
		if (array)
			free(array);
		return (NULL);
	}
	array[*len_array] = 0;
	return (array);
}

static t_token	*fill_cmd(t_shell **shell, t_token *tokens)
{
	int		i;
	int		len_array;
	char	**array;

	if (!tokens)
		return (NULL);
	array = fill_data(tokens, &i, &len_array);
	while (tokens)
	{
		if (is_redirection(tokens) > 0)
		{
			handle_redirection_token(tokens, (*shell)->cmd);
			next_tokens(&tokens, 2);
		}
		else if (ft_strncmp(tokens->value, "|", 2) == 0)
			break ;
		else if (array && tokens && ++i <= len_array - 1)
		{
			array[i] = ft_strdup(tokens->value);
			tokens = tokens->next;
		}
	}
	(*shell)->cmd->cmd = array;
	return (tokens);
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
		else
		{
			tokens = fill_cmd(shell, tokens);
			next_tokens(&tokens, 0);
		}
	}
	(*shell)->cmd = tmp;
	return (0);
}
