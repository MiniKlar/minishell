#include "minishell.h"

char	*join_token(t_token *tokens)
{
	char *tmp;
	char *tokens_lst;

	tokens_lst = NULL;
	while (tokens != NULL)
	{
		if (tokens_lst == NULL)
			tokens_lst = ft_strdup("");
		tmp = tokens_lst;
		tokens_lst = ft_strjoin(tokens_lst, tokens->value);
		free(tmp);
		tmp = tokens_lst;
		tokens_lst = ft_strjoin(tokens->value, " ");
		free(tmp);
		tokens = tokens->next;
	}
	return (tokens_lst);
}
