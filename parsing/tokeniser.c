#include "minishell.h"

void	ft_add_token(t_token *tokens, char *buffer, size_t *buffer_len)
{
	buffer[*buffer_len] = '\0';
	tokens->tokens[tokens->nb_tokens] = ft_strdup(buffer);
	tokens->nb_tokens++;
	*buffer_len = 0;
}

void	ft_handle_depth(char c, int *depth, char *buffer, size_t *buffer_len)
{
	if (c == '(')
	{
		(*depth)++;
		buffer[*buffer_len] = c;
		(*buffer_len)++;
	}
	else if (c == ')')
	{
		(*depth)--;
		if (*depth != 0)
			buffer[*buffer_len] = c;
		(*buffer_len)++;
	}
	else
	{
		buffer[*buffer_len] = c;
		(*buffer_len)++;
	}
}

void	ft_process_char(t_token *t, char c, int *depth, size_t *buf_l, char *b)
{
	if (*depth == 0)
	{
		if (c == ' ')
		{
			if (*buf_l > 0)
				ft_add_token(t, b, buf_l);
		}
		else if (c == '(')
		{
			if (*buf_l > 0)
				ft_add_token(t, b, buf_l);
			*depth = 1;
		}
		else
			b[(*buf_l)++] = c;
	}
	else
		ft_handle_depth(c, depth, b, buf_l);
}

void	ft_finalize_tokens(t_token *tokens, char *buffer, size_t *buffer_len)
{
	if (*buffer_len > 0)
		ft_add_token(tokens, buffer, buffer_len);
	tokens->tokens[tokens->nb_tokens] = NULL;
}

void	ft_strtok(t_token *tokens, char *str)
{
	size_t	i;
	int		depth;
	char	buffer[1024];
	size_t	buffer_len;

	i = 0;
	depth = 0;
	buffer_len = 0;
	tokens->nb_tokens = 0;
	tokens->tokens = malloc(sizeof(char *) * (ft_nb_tokens(str) + 2));
	if (!tokens->tokens)
		return ;
	while (str[i])
	{
		ft_process_char(tokens, str[i], &depth, &buffer_len, buffer);
		i++;
	}
	ft_finalize_tokens(tokens, buffer, &buffer_len);
}
