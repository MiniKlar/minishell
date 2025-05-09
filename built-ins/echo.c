#include "minishell.h"

char *get_home(char *str);

int ft_echo(char **command, t_tmp_env *node)
{
	size_t i;
	char *tilde;
	char *ptr;
	bool has_arg = false;
	i = 0;
	if (command[1] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (strncmp(command[1], "-n", 2) == 0)
	{
		has_arg = true;
		i++;
	}
	while (command[++i] != NULL)
	{
		if (strncmp(command[i], "~", 1) == 0 && command[i][1] == '\0')
		{
			tilde = getenv("HOME");
			if (tilde == NULL)
				tilde = pwd(false);
			ft_putstr_fd(get_home(tilde), 1);
		}
		else if (strncmp(command[i], "$", 1) == 0)
		{
			ptr = find_param(command[i], node);
			if (ptr)
				ft_putstr_fd(ptr, 1);
			free(ptr);
		}
		else
			ft_putstr_fd(command[i], 1);
		if (command[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (!has_arg)
		ft_putstr_fd("\n", 1);
	return (0);
}

char *get_home(char *str)
{
	size_t i;
	size_t k;
	char *tilde;

	i = 0;
	k = 0;
	while (i != 3)
	{
		if (str[k] == '/')
			i++;
		k++;
	}
	tilde = ft_substr(str, 0, k - 1);
	return (tilde);
}

// - Created readline test zith add_history skipping an empty line.
// - Created echo built-ins. Implemented the basic echo, at the moment it's printing full sentence correctly w/ -n and without. Need to add $ expansion.
// - Added ~ expansian for echo with and without env!
// - Exit is now working, need to see for the exit code.
