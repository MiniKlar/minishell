#include "../LIB_SHELL/lib_shell.h"
#include "../includes/parsing.h"

void next_tokens(t_token **tokens, int i);

int	syntax_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (0);
}

t_token	*tokenisation(t_shell *shell, char *line)
{
	t_token	*tokens;
	bool	in_quote;
	size_t	i;
	size_t	k;

	tokens = NULL;
	in_quote = false;
	i = 0;
	k = 0;
	if (line[0] == '\0' || line[0] == ':' || line[0] == '!')
		return (NULL);
	while (line[i] != '\0')
	{
		if ((line[i] == '"' || line[i] == '\'') && !in_quote)
			in_quote = true;
		if ((line[i] == ';' || line[i] == '\\') && !in_quote) //si c'est character non gerable
		{
			handle_syntax_error(shell, &tokens, line[i]); //on envoie une erreur
			return (NULL);
		}
		while (line[i] && ft_isspace(line[i]) && !in_quote) //pendant qu'il y a la ligne de commande, que cest isspace et que cest pas une quote, on avance
			i++;
		if (!line[i])
			break ;
		if (is_metacharacter(line + i) && !in_quote) //si cest un metacharacter et que cest pas une quote
			i = handle_metacharacter(&tokens, line, i); //on gere les metacharacter et on les tokenise
		else
		{
			k = handle_regular_token(shell, &tokens, line + i, &in_quote);
			if (k == 0)
				return (NULL);
			else
				i += k;
		}
		if (line[i])
			i++;
	}
	return (tokens);
}

size_t	calcul_len_tokens(t_token *tokens)
{
	size_t	i;

	i = 0;
	if (!tokens)
		return (0);
	while (tokens)
	{
		if (ft_strncmp(tokens->value, "|", ft_strlen(tokens->value)) == 0)
				break;
		else if (is_redirection(tokens) != 0)
			tokens->next = tokens->next;
		else
			i++;
		tokens = tokens->next;
	}
	return (i);
}

void	fill_cmd(t_shell **shell, t_token *tokens)
{
	size_t	len_array;
	size_t	i;
	char	**array;

	if (!tokens)
		return ;
	else
	{
		i = 0;
		len_array = calcul_len_tokens(tokens);
		printf("VOICI LEN_ARRAY = %zu\n", len_array);
		array = malloc(sizeof(char *) * (len_array + 1));
		if (!array)
			return ;
		array[len_array] = 0;
		while (i != len_array)
		{
			if (is_redirection(tokens) != 0)
				tokens = tokens->next->next;
			array[i] = ft_strdup(tokens->value);
			i++;
			tokens = tokens->next;
		}
		print_array(array);
		(*shell)->cmd->cmd = array;
	}
}

int	process_token(t_shell **shell, t_token *tokens)
{
	t_cmd *tmp;

	tmp = (*shell)->cmd;
	while (tokens != NULL)
	{
		if (ft_strncmp(tokens->value, "|", ft_strlen(tokens->value)) == 0)
		{
			(*shell)->nb_pipe++;
			(*shell)->cmd->next = init_cmd(NULL);
			(*shell)->cmd = (*shell)->cmd->next;
			next_tokens(&tokens, 1);
		}
		else if (is_redirection(tokens) != 0)
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

void next_tokens(t_token **tokens, int i)
{
	int	index;

	index = 0;
	if (!tokens)
		return ;
	if (i == 1)
		*tokens = (*tokens)->next; // apres un pipe
	else if (i == 2)
	{
		while (index != i)
		{
			if ((*tokens) != NULL)
			{
				printf("VOICI TOKEN REDIR %s\n", (*tokens)->value);
				(*tokens) = (*tokens)->next; //pour avancer apres une redir
			}
			index++;
		}
	}
	else
	{
		while (*tokens)
		{
			if (is_redirection((*tokens)) != 0 || ft_strncmp((*tokens)->value, "|", ft_strlen((*tokens)->value)) == 0)
				break;
			else
				*tokens = (*tokens)->next;
		}
	}
}

t_shell	*parse_tokens(t_shell *shell, t_token *tokens)
{
	shell->cmd = init_cmd(NULL);
	if (!shell->cmd)
	{
		ft_putstr_fd("Error memory allocation shell->cmd", 2);
		exit(EXIT_FAILURE);
	}
	process_token(&shell, tokens);
	return (shell);
}
