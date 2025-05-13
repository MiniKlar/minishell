#include "minishell.h"

void	free_execve_error(t_shell *tok, t_pipe *p, char **c_arg, char *c_path)
{
	free(c_path);
	free_tab(c_arg);
	free_shell(tok);
	free_struct_pipe(p);
}

void	free_tab(char **tableau)
{
	int	i;

	i = 0;
	while (tableau[i] != 0)
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
}

void	free_env(t_envp *node)
{
	t_envp	*tmp;

	if (node == NULL)
		return ;
	else
	{
		while (node)
		{
			free(node->envp);
			tmp = node->next;
			free(node);
			node = tmp;
		}
	}
}

void	free_shell(t_shell *node)
{
	t_shell	*tmp;

	if (node == NULL)
		return ;
	else
	{
		while (node)
		{
			free(node->shell);
			tmp = node->next;
			free(node);
			node = tmp;
		}
	}
}

void	free_params(t_tmp_env *node)
{
	t_tmp_env	*tmp;

	if (node == NULL)
		return ;
	else
	{
		while (node)
		{
			free(node->name);
			free(node->valeur);
			tmp = node->next;
			free(node);
			node = tmp;
		}
	}
}

void free_struct_pipe(t_pipe *pipex)
{
	free(pipex->fdpipe);
	free(pipex);
}
