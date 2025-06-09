#include "../LIB_SHELL/lib_shell.h"
#include "../includes/parsing.h"

void	next_tokens(t_token **tokens, int i);

int	syntax_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (0);
}

char	find_next_quote(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			break;
		else
			i++;
	}
	return (line[i]);
}

size_t	progress_index_in_quote(char *line, size_t i)
{
	size_t	index_matching_quote;

	index_matching_quote = find_corresponding_quote(line + i, line[i]);
	if (index_matching_quote == 0)
		return (0);
	if (index_matching_quote != 0)
	{
		while (index_matching_quote != 0)
		{
			i++;
			index_matching_quote--;
		}
	}
	return (i);
}

t_token	*fill_raw_tokens(t_shell *shell, t_token **raw_tokens, char *line)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	*raw_tokens = init_token(""); //peut etre supprimer la toute premiere node.
	if (line[0] == '\0' || line[0] == ':' || line[0] == '!')
	{
		free((*raw_tokens)->value);
		free(*raw_tokens);
		return (NULL);
	}
	while (ft_isspace(line[i]) == true)
		i++;
	k = i;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			if (line[i - 1] != ' ')
				add_token(raw_tokens, line + k, i - k, false);
			k = i + 1;
		}
		else if ((line[i] == ';' || line[i] == '\\'))
		{
			handle_syntax_error(shell, raw_tokens, line[i]);
			return (NULL);
		}
		else if (line[i] == '\'' || line[i] == '"')
		{
			if (progress_index_in_quote(line, i) == 0)
			{
				if (k == 0)
					unexpected_quote(shell, *raw_tokens, find_next_quote(line + i));
				else
					unexpected_quote(shell, *raw_tokens, find_next_quote(line + k));
				return (NULL);
			}
			else
				i = progress_index_in_quote(line, i);
		}
		i++;
	}
	if (line[i - 1] != ' ')
		add_token(raw_tokens, line + k, i, true);
	return (*raw_tokens);
}

t_token	*tokenisation(t_shell *shell, char *line)
{
	t_token	*raw_tokens;

	raw_tokens = fill_raw_tokens(shell, &raw_tokens, line);
	if (!raw_tokens)
		return (NULL);
	ft_del_first_raw_tokens(&raw_tokens);
	return (raw_tokens);
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
		else if (is_redirection(tokens) > 0)
			tokens = tokens->next;
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
		printf("len_array = %zu\n", len_array);
		array = malloc(sizeof(char *) * (len_array + 1));
		if (!array)
			return ;
		array[len_array] = 0;
		while (i <= len_array - 1)
		{
			if (is_redirection(tokens) > 0 || ft_strncmp(tokens->value, "|", 2) == 0)
				tokens = tokens->next;
			else if (tokens)
				array[i] = ft_strdup(tokens->value);
			i++;
			if (tokens)
				tokens = tokens->next;
		}
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
		else if (is_redirection(tokens) > 0)
		{
			handle_redirection_token(tokens, (*shell)->cmd);
			next_tokens(&tokens, 2);
		}
		else
		{
			printf("tu vas fill cmd\n");
			fill_cmd(shell, tokens);
			next_tokens(&tokens, 0);
		}
	}
	(*shell)->cmd = tmp;
	(*shell)->first_cmd = (*shell)->cmd;
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
				(*tokens) = (*tokens)->next; //pour avancer apres une redir
			index++;
		}
	}
	else
	{
		while (*tokens)
		{
			if (is_redirection((*tokens)) > 0 || ft_strncmp((*tokens)->value, "|", 2) == 0)
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

bool	check_if_quote_exist(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			return (true);
		i++;
	}
	return (false);

}

char	*fill_str_without_quote(char *line, size_t *index)
{
	size_t	i;
	size_t	k;
	char	*str;
	char	*tmp;
	char	*tmp_env;

	i = 0;
	k = 0;
	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			break;
		else if (line[i] == '$')
		{
			if (line[0] != '$')
			{
				tmp = str;
				tmp_env = ft_substr(line + k, 0, i);
				str = ft_strjoin(str, tmp_env);
				free(tmp);
				free(tmp_env);
			}
			tmp = str;
			printf("TU ES ICI\n");
			tmp_env = handle_env_variable(line + i + 1, &i);
			k = i + 1;
			str = ft_strjoin(str, tmp_env);
			free(tmp);
			free(tmp_env);
		}
		else
			i++;
	}
	tmp = str;
	tmp_env = ft_substr(line + k, 0, i);
	str = ft_strjoin(str, tmp_env);
	free(tmp);
	free(tmp_env);
	*index += i;
	printf("VOICI LA STR FINALE = %s\n", str);
	return (str);
}

char	*fill_str_with_quote(char *line, size_t *index)
{
	size_t	i;
	size_t	k;
	char	*str;
	char	*tmp_env_variable;
	char	*tmp;

	i = 1;
	k = i;
	str = ft_strdup("");
	if (!str)
		return (NULL);
	if (line[0] == line[i])
	{
		*index += i + 1;
		return (ft_strdup(""));
	}
	while (line[i])
	{
		if (line[i] == line[0])
		{
			if (str)
			{
				tmp = str;
				printf("voici l\'index i = %zu et le char line[i] = %c", i, line[i]);
				printf("voici l\'index k = %zu et le char line[k] = %c", k, line[k]);
				tmp_env_variable = ft_substr(line + k, 0, i - k);
				str = ft_strjoin(str, tmp_env_variable);
				free(tmp);
				free(tmp_env_variable);
				*index += i + 1;
				return (str);
			}
			else
			{
				*index += i + 1;
				return (ft_substr(line + k, 0, i - k));
			}
		}
		else if (line[i] == '$' && line[0] == '"')
		{
			tmp_env_variable = handle_env_variable(line + i + 1, &i);
			tmp = str;
			str = ft_strjoin(str, tmp_env_variable);
			printf("voici str après join handle env = %s\n",str);
			i++;
			k = i;
			free(tmp);
			free(tmp_env_variable);
		}
		else
		{
			tmp = str;
			tmp_env_variable = ft_substr(line + i, 0, 1);
			str = ft_strjoin(str, tmp_env_variable);
			free(tmp);
			free(tmp_env_variable);
			i++;
			k = i;
		}
	}
	return (NULL);
}

char	*handle_quote(char *str_to_parse)
{
	char	*line;
	char	*str;
	char	*tmp;
	char	quote;
	size_t	i;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	i = 0;
	while (str_to_parse[i])
	{
		str = NULL;
		quote = str_to_parse[i];
		if (quote == '\'' || quote == '"')
		{
			str = fill_str_with_quote(str_to_parse + i, &i);
			printf("voici str with quote = %s\n", str);
			if (!str)
				return (NULL);
		}
		else
		{
			printf("tu es ici\n");
			str = fill_str_without_quote(str_to_parse + i, &i);
		}
		tmp = line;
		line = ft_strjoin(line, str);
		free(tmp);
		free(str);
	}
	printf("voici la line finale de la fonction globale = %s\n", line);
	return (line);
}

t_token	*proccess_raw_tokens(t_token *raw_tokens)
{
	t_token	*tokens;
	char	*str;

	tokens = init_token("");
	while (raw_tokens)
	{
		str = handle_quote(raw_tokens->value);
		free(raw_tokens->value);
		raw_tokens->value = str;
		add_token(&tokens, str, 0, true);
		raw_tokens = raw_tokens->next;
	}
	ft_del_first_raw_tokens(&tokens);
	return (tokens);
}
