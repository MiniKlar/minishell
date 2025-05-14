/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:53:30 by lomont            #+#    #+#             */
/*   Updated: 2025/05/12 23:38:15 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	t_shell	*shell;
	char *str;
	shell = malloc(sizeof(t_shell));
	str = readline("caca ");
	ft_strtok(shell, str, ' ');
	// printf("Premier token: %s\n", shell->shell[0]);
	// printf("Deuxieme token: %s\n", shell->shell[1]);
	// printf("Troisieme token: %s\n", shell->shell[2]);
	// printf("Quatrieme token: %s\n", shell->shell[3]);
	free_tab(shell->shell);
	free(shell);
	return (0);
}
