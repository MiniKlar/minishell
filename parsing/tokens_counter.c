#include "minishell.h"

void	no_depth_case(char c, int *depth, int *in_token, int *count)
{
	if (*depth > 0)
	{
		if (c == '(')
			(*depth)++;
		else if (c == ')')
		{
			(*depth)--;
			if (*depth == 0)
			{
				(*count)++;
				*in_token = 0;
			}
		}
	}
}

int	ft_nb_tokens_core(char c, int *depth, int *in_token, int *count)
{
	if (*depth == 0)
	{
		if (c == ' ')
		{
			if (*in_token)
			{
				(*count)++;
				*in_token = 0;
			}
		}
		else if (c == '(')
		{
			if (*in_token)
				(*count)++;
			*in_token = 1;
			*depth = 1;
		}
		else
		{
			if (!*in_token)
				*in_token = 1;
		}
	}
	no_depth_case(c, depth, in_token, count);
	return (0);
}

int	ft_nb_tokens(char *str)
{
	int		count;
	int		depth;
	size_t	i;
	int		in_token;

	count = 0;
	depth = 0;
	i = 0;
	in_token = 0;
	while (str[i])
	{
		ft_nb_tokens_core(str[i], &depth, &in_token, &count);
		i++;
	}
	if (in_token)
		count++;
	return (count);
}
