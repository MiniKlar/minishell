#include "minishell.h"

t_params	*add_parameters(char *str, t_params *node)
{
	t_params *tmp;
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

void	ft_delone(t_params *lst, void (*del)(void*))
{
	del(lst->name);
	del(lst->valeur);
	free(lst);
}

void	ft_clear(t_params **lst, void (*del)(void*))
{
	t_params	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ft_delone(*lst, del);
		*lst = tmp;
	}
}
