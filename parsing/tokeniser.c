#include "minishell.h"

static void	add_token_from_buf(t_token **tokens, char *buffer, size_t *buffer_len)
{
	if (*buffer_len > 0)
	{
		if (*buffer_len >= 1024)
			*buffer_len = 1023;
		buffer[*buffer_len] = '\0';
		token_add_back(tokens, init_token(ft_strdup(buffer), NONE, NULL));
		*buffer_len = 0;
	}
}

static void	process_subshell(t_token **tokens, char *str, size_t *i, t_cmd *cmds)
{
	size_t	start = *i;
	size_t	pos = start + 1;
	int		depth = 1;
	char	subshell[1024];
	size_t	len = 0;

	while (str[pos] && depth > 0 && len < 1023)
	{
		if (str[pos] == '(')
			depth++;
		else if (str[pos] == ')')
			depth--;
	
		if (depth > 0)
			subshell[len++] = str[pos];
		pos++;
	}
	subshell[len] = '\0';
	if (depth != 0)
		return ;

	add_token_from_buf(tokens, subshell, &len);
	*i = pos - 1;
	cmds->is_subshell = true;
}

void	ft_strtok(t_token **tokens, char *str, t_cmd *cmds)
{
	size_t	i = 0;
	char	buffer[1024];
	size_t	buffer_len = 0;

	while (str[i])
	{
		if (str[i] == '(')
		{
			add_token_from_buf(tokens, buffer, &buffer_len);
			process_subshell(tokens, str, &i, cmds);
		}
		else if (str[i] == ' ')
			add_token_from_buf(tokens, buffer, &buffer_len);
		else
		{
			if (buffer_len < 1023)
				buffer[buffer_len++] = str[i];
			else
				add_token_from_buf(tokens, buffer, &buffer_len);
		}
		i++;
	}
	add_token_from_buf(tokens, buffer, &buffer_len);
}
