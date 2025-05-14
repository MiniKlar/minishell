#include "minishell.h"

void	free_redir_struct(t_redir *redirections);
void	free_struct_pipe(t_pipe *pipex);
void	free_shell(t_shell *shell);

void	free_all(t_shell *shell, t_pipe *pipex)
{
	free_shell(shell);
	free_struct_pipe(pipex);
	exit(EXIT_FAILURE);
}

void	free_shell(t_shell *shell)
{
	t_shell	*tmp;

	if (shell == NULL)
		return ;
	else
	{
		while (shell != NULL)
		{
			free_tab(shell->cmd);
			free_redir_struct(shell->redir);
			tmp = shell;
			shell = shell->next;
			free(tmp);
		}
	}
}

void	free_struct_pipe(t_pipe *pipex)
{
	if (pipex->fdpipe != NULL)
		free(pipex->fdpipe);
	free(pipex);
}

void free_redir_struct(t_redir *redirections)
{
	t_redir	*tmp;

	while (redirections != NULL)
	{
		tmp = redirections;
		free(redirections->str);
		redirections = redirections->next;
		free(tmp);
	}
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
