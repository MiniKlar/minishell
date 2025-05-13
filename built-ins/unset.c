#include "minishell.h"

void	unset(t_shell	*shell)
{
	char *name_to_unset;
	t_envp *env;
	size_t	i;

	i = 0;
	shell = shell->next;
	name_to_unset = shell;
	while (name_to_unset[i])
	{
		if (ft_isalnum(name_to_unset[i]) != 1)
			return ;
		i++;
	}
	env = append_envp(name_to_unset, envp);
	ft_delone(ft_last_envp(env));
	envp = ft_transform_envp(env);		//mettre dans la struct avec le bon env.
}
