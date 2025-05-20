#include "minishell.h"

char	**ft_malloc_envp(char **envp)
{
	char	**alloc_envp;
	int		i;
	int		k;
	i = 0;
	while (envp[i])
		i++;
	alloc_envp = malloc(sizeof(char *) * (i));
	if (!alloc_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		k = 0;
		while (envp[i][k] != '\0')
			k++;
		alloc_envp[i] = malloc(sizeof(char) * (k + 1));
		if (!alloc_envp[i])
			return (NULL);
		ft_memmove(alloc_envp[i], envp[i], k);
		alloc_envp[i][k] = '\0';
		i++;
	}
	alloc_envp[i - 1] = NULL;
	return (alloc_envp);
}

int	ft_nb_shell(char *str)
{
	size_t i;
	size_t k;

	i = 0;
	k = 1;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == ' ')
			k++;
		i++;
	}
	return (k);
}

t_envp	*create_node_envp(char *env)
{
	t_envp	*new_env;

	new_env = malloc(sizeof(*new_env));
	if (!new_env)
		return (NULL);
	new_env->envp = ft_strdup(env);
	new_env->next = NULL;
	return (new_env);
}

t_envp	*fill_envp(t_envp *node, char **envp)
{
	t_envp *new_node;
	size_t	i;

	i = 0;
	while (envp[i])
	{
		new_node = create_node_envp(envp[i]);
		ft_add_back_envp(&node, new_node);
		i++;
	}
	return (node);
}
