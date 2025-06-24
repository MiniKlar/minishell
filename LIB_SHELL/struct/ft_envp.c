/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:35:23 by lpatin            #+#    #+#             */
/*   Updated: 2025/06/24 17:35:24 by lpatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

char	**ft_malloc_envp(char **envp)
{
	char	**alloc_envp;
	int		i;
	int		k;

	i = 0;
	while (envp[i])
		i++;
	alloc_envp = malloc(sizeof(char *) * (i + 1));
	if (!alloc_envp)
		return (NULL);
	alloc_envp[i] = NULL;
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
	return (alloc_envp);
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
	t_envp	*new_node;
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

void	ft_add_back_envp(t_envp **lst, t_envp *new)
{
	t_envp	*current;

	if (*lst == NULL)
		*lst = new;
	else
	{
		current = ft_last_envp(*lst);
		current->next = new;
	}
}

t_envp	*ft_last_envp(t_envp *lst)
{
	t_envp	*tmp;

	if (lst == NULL)
		return (lst);
	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
	}
	return (tmp);
}
