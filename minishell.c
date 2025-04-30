/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:53:30 by lomont            #+#    #+#             */
/*   Updated: 2025/04/30 03:36:37 by lpatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	t_token	*tokens;
	char *str;
	tokens = malloc(sizeof(t_token));
	str = readline("caca ");
	ft_strtok(tokens, str, ' ');
	printf("Premier token: %s\n", tokens->tokens[0]);
	printf("Deuxieme token: %s\n", tokens->tokens[1]);
	printf("Troisieme token: %s\n", tokens->tokens[2]);
	printf("Quatrieme token: %s\n", tokens->tokens[3]);
	free_tab(tokens->tokens);
	free(tokens);
	return (0);
}
