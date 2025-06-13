#include "../LIB_SHELL/lib_shell.h"
#include "../includes/parsing.h"

char	*check_getenv(char *str)
{
	char	*env;

	env = NULL;
	if (!str)
		return (NULL);
	else
	{
		env = getenv(str);
		if (!env)
		{
			printf("ENV NOT FOUND\n");
			free(str);
			return (NULL);
		}
		else
		{
			free(str);
			return (ft_strdup(env));
		}
	}
}

char	*append_single_quotes(char *str)
{
	char	*new_str;
	char	*tmp;
	if (!str)
		return (NULL);
	tmp = NULL;
	new_str = ft_strjoin("\'", str);
	tmp = new_str;
	new_str = ft_strjoin(new_str, "\'");
	free(tmp);
	free(str);
	return (new_str);
}

char *handle_env_variable(char *str, size_t *index_parsing, int exit_code)
{
	char	*env_variable;
	size_t	i;

	i = 0;
	if (str[0] == '?')
	{
		env_variable = ft_itoa(exit_code);
		i++;
	}
	else
	{
		while (str[i])
		{
			if (ft_isalnum(str[i]) == 0)
				break;
			else
				i++;
		}
		env_variable = check_getenv(ft_substr(str, 0, i));
	}
	if (index_parsing)
		*index_parsing += i;
	if (!env_variable)
		return (NULL);
	return (env_variable);
}
