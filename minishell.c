/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:53:30 by lomont            #+#    #+#             */
/*   Updated: 2025/04/29 04:29:09 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdlib.h>
#include </usr/include/stdio.h>
#include </usr/include/readline/readline.h>
#include </usr/include/readline/history.h>

typedef struct s_token
{
	char **tokens;
	size_t nb_tokens;
}			t_token;

int ft_nb_tokens(char *str)
{
	size_t i;
	size_t k;

	i = 0;
	k = 1;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == ' ')
			k++;
		i++;
	}
	return (k);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void set_caca(char *str, size_t i, t_token *tokens)
{
	size_t k;
	size_t j;

	j = 0;
	k = i - 1;
	while(str[k] != ' ' && k != 0)
		k--;
	if (strlen(str) == i || k != 0)
		k++;
	tokens->tokens[tokens->nb_tokens] = malloc(sizeof(char) * (i - k + 1));
	while (k != i)
	{
		tokens->tokens[tokens->nb_tokens][j] = str[k];
		j++;
		k++;
	}
	tokens->tokens[tokens->nb_tokens][j] = '\0';
	tokens->nb_tokens++;
}

void	ft_strtok(t_token *tokens, char *str, char delimiter)
{
	size_t i;

	i = 0;
	tokens->nb_tokens = 0;
	tokens->tokens = malloc(sizeof(char *) * (ft_nb_tokens(str) + 1));
	if (!tokens->tokens)
		return ;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == delimiter)
			set_caca(str, i, tokens);
		i++;
	}
	set_caca(str, i, tokens);
	tokens->tokens[tokens->nb_tokens] = NULL;
}

int main(void)
{
	t_token	*tokens;
	char *str;
	tokens = malloc(sizeof(t_token));
	str = readline("caca ");
	ft_strtok(tokens, str, ' ');
	//printf("Premier token: %s\n", tokens->tokens[0]);
	//printf("Deuxieme token: %s\n", tokens->tokens[1]);
	//printf("Troisieme token: %s\n", tokens->tokens[2]);
	//printf("Quatrieme token: %s\n", tokens->tokens[3]);
	free_tab(tokens->tokens);
	free(tokens);
	return (0);
}

// 	int i;

// 	i = 0;
// 	while (i < 5)
// 	{
// 		str = readline("caca ");
// 		add_history(str);
// 		printf("%s\n", str);
// 		i++;
// 	}
// 	return (0);
// }
