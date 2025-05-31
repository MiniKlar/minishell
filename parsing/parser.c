#include "../LIB_SHELL/lib_shell.h"
#include "../includes/parsing.h"

void	add_pipe_to_shell(t_shell *shell, t_cmd *cmd)
{
	cmd_add_back(&shell->cmd, cmd);
	shell->nb_pipe++;
}

int	handle_redirection_token(t_token *tokens, t_cmd *cmd)
{
	handle_redirection(tokens, cmd);
	return (0);
}
size_t	find_corresponding_quote(char *line, char quote_to_find)
{
	size_t	i;

	i = 1;
	printf("voici quote to find = %c\n", quote_to_find);
	printf("voici line + 1 = %c\n", line[i]);
	while (line[i])
	{
		if (line[i] == quote_to_find)
			return (i);
		else
			i++;
	}
	return (0);
}

int	handle_regular_token(t_shell *shell, t_token **tokens, char *line, bool *in_quote)
{
	char	*old_token;
	char	*new_token;
	char	*tmp;
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	old_token = NULL;
	new_token = NULL;
	while (line[i])
	{
		if (new_token)
		{
			old_token = new_token;
			new_token = NULL;
		}
		if (line[i] == ' ')
			break;
		if ((line[i] == '\'' || line[i] == '"') && *in_quote == false)
			*in_quote = true;
		if (*in_quote == true)
		{
			new_token = ft_substr(line, k, i); // on recupere le token sans guillemets pour lajouter apres;
			if (old_token) //on l'ajoute au précédent token s'il y en a 1
			{
				tmp = old_token;
				old_token = ft_strjoin(old_token, new_token);
				free(new_token);
				free(tmp);
			}
			else
			{
				old_token = new_token;
				new_token = NULL;
			}
			k = find_corresponding_quote(line + i, line[i]);
			if (k == 0)
			{
				unexpected_quote(shell, *tokens, line[i]);
				free(old_token);
				return (0);
			}
			else
			{
				new_token = ft_substr(line, i + 1, k - 1);
				if (old_token)
				{
					tmp = new_token;
					new_token = ft_strjoin(old_token, new_token);
					free(old_token);
					free(tmp);
				}
				*in_quote = false;
				i += k;
			}
		}
		i++;
	}
	if (k == 0)
		add_token(tokens, line, i, k);
	else
	{
		if (!new_token)
		{
			new_token = ft_substr(line, k, i);
			tmp = new_token;
			new_token = ft_strjoin(old_token, new_token);
		}
		add_token(tokens, new_token, 0, k);
		free(new_token);
	}
	if (*in_quote == true)
		return (0);
	return (i);
}
