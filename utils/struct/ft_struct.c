#include "minishell.h"

t_tmp_env	*add_parameters(char *str, t_tmp_env *node)
{
	t_tmp_env *tmp;
	size_t		i;
	size_t		k;

	i = 0;
	tmp = create_node_param();
	while(str[i] != '=')
		i++;
	tmp->name = ft_substr(str, 0, i);
	tmp->signe = str[i];
	k = i + 1;
	while(str[++i] != '\0')
		;
	tmp->valeur = ft_substr(str, k, i - k);
	ft_add_front(&node, tmp);
	return (tmp);
}

void	ft_delone(t_tmp_env *lst, void (*del)(void*))
{
	del(lst->name);
	del(lst->valeur);
	free(lst);
}

void	ft_delone_env(t_envp *lst, char *env_to_find)
{
	t_envp *node_before_env_to_find;
	t_envp *tmp;

	tmp = NULL;
	if (!lst)
		return ;
	else
	{
		while (lst != NULL)
		{
			if (ft_strncmp(lst->envp, env_to_find, ft_strlen(env_to_find)) == 0)
			{
				printf("VOICI ENVP %s\n", lst->envp);
				tmp = lst->next;
				break ;
			}
			node_before_env_to_find = lst;
			lst = lst->next;
		}
		free(lst->envp);
		free(lst);
		node_before_env_to_find->next = tmp;
	}
}

void	ft_clear(t_tmp_env **lst, void (*del)(void*))
{
	t_tmp_env	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ft_delone(*lst, del);
		*lst = tmp;
	}
}
