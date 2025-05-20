#include "minishell.h"

void	create_child(t_shell *node, t_pipe *pipex);
void	create_children(t_shell *shell, pid_t *id_fork, t_pipe *pipex);
int		ft_wait(t_shell *shell, pid_t *id_fork, size_t nb_pipes);
pid_t	*fork_cmd(t_shell *shell, t_pipe *pipex);
void	redir_cmd_input_output(t_shell *shell);
int		dup_pipe(t_shell *shell, t_pipe *pipex);
void	ft_dup(t_shell *shell, t_pipe *pipex, char *command_path);
void	ft_dup_redir(t_shell *shell);

int	exec_cmd(t_shell *shell)
{
	t_pipe	*pipex;		//déclaration de ma struct pipex pour stocker données pour mes piepes.
	pid_t	*id_fork;	//déclaration init_fork pour stocker les pids de mes enfants.

	if (shell->nb_pipe != 0)	//si le nombre de pipe est à 0 (donc je n'ai qu'un child a créer)
		pipex = set_struct_pipex(shell);	//alors je remplis ma structure
	else
		pipex = NULL;	//sinon pipex init a NULL
	id_fork = fork_cmd(shell, pipex); //init du nombres d'enfants
	if (pipex->fdpipe != NULL)
		ft_close_fdpipe(pipex);
	shell->wstatus = ft_wait(shell, id_fork, shell->nb_pipe);
	if (WIFEXITED(shell->wstatus) && WEXITSTATUS(shell->wstatus))
		return (WEXITSTATUS(shell->wstatus));
	free(id_fork);
	free_struct_pipe(pipex);
	return (0);
}

pid_t	*fork_cmd(t_shell *shell, t_pipe *pipex)
{
	size_t	nb_fork;
	pid_t	*id_fork;

	if (shell->nb_pipe == 0) //si nb_pipe = 0
		nb_fork = 1;	//alors nb enfant = 1
	else
		nb_fork = shell->nb_pipe + 1; //sinon nb enfant = nb pipe = nb commande
	id_fork = malloc(sizeof(pid_t) * (nb_fork + 1)); //alloue memoire des id enfants
	id_fork[nb_fork] = 0;	//on met a zero le dernier pour dire qu'il n'y a plus d'enfant.
	if (!id_fork) //si alloc echoue
	{
		printf("Error malloc id_fork");
		free_all(shell, pipex); //free tout
	}
	else
		create_children(shell, id_fork, pipex); //sinon creation des childs
	return (id_fork);	//on retourne tout les id des enfants.
}

void	create_children(t_shell *shell, pid_t *id_fork, t_pipe *pipex)
{
	size_t	i; //declaration index

	i = 0; //init a 0 index.
	while (shell->cmd != NULL) //tant qu'il y a des commandes
	{
		id_fork[i] = fork();	//on fork puis on met dans la variable id_fork le numero de lenfant
		if (id_fork[i] == -1) //si ca echoue
		{
			printf("Error fork id_fork[%zu]", i);
			free(id_fork);
			free_all(shell, pipex); //on free tout
		}
		//init avec fonction pipe fdpipe[] selon le nb pipe + le i
			//si 1 pipe
				//alors	fdpipe[2 * nb_pipe]
			//si 2 pipe
				//alors fdpipe[2 * nb_pipe]
			// si 3 pipe ou plus fdpipe[2 * 3]
				// 1 0 3 2
				//fdpipe[]
		else if (id_fork[i] == 0) //si c'est 0
			create_child(shell, pipex); //on cree lenfant
		pipe_struct_update(shell, pipex, i); //on met a jour la struct pipe pour la prochaine commande.
		shell->cmd = shell->cmd->next; //on avant dans les commandes.
		i++; //on avance dans l'index des id fork.
	}
}

void	create_child(t_shell *shell, t_pipe *pipex)
{
	char	*command_path; //on initialise la string pour placer notre path de commande
	bool	is_built_ins;	//on crée un boolean pour savoir si cest un built in

	//printf("TU ES DANS LENFANT\n");
	is_built_ins = is_cmd_built_ins(shell);	//on check si cest un builtin
//	printf("VOICI IS BUILT INS %d\n", is_built_ins);
	if (!is_built_ins) //si ce nest pas un built in
		command_path = find_command_exist_executable(shell, pipex); //on va check la commande si elle existe
	redir_cmd_input_output(shell); //redirection in et out (infile, outfile, heredoc)
	ft_dup_redir(shell); //dup le fd_in et fd_out
	if (shell->nb_pipe != 0) //si il y a des pipesa
		ft_dup(shell, pipex, command_path); //dup les pipes
	if (is_built_ins) //si cest un built in
	{
		exec_built_in(shell); //exec built in
		exit(shell->wstatus); // exit wstatus
	}
	else if (execve(command_path, &shell->cmd->cmd[0], shell->envp) == -1) //sinon execve
	{
		perror("ERROR EXEC VE");
		free_all(shell, pipex);
		free(command_path);
		exit(126);
	}
}

void	redir_cmd_input_output(t_shell *shell)
{
	char		*heredoc_name;
	e_symbol	type_redir;
	int			i;

	i = 0;
	heredoc_name = NULL;
	while (shell->cmd->redir != NULL)
	{
		type_redir = shell->cmd->redir->symbol;
		if (type_redir == REDIR_IN)
			redir_infile(shell);
		else if (type_redir == REDIR_OUT || type_redir == APPEND)
			redir_outfile(shell);
		else if (type_redir == HERE_DOC)
		{
			heredoc_name = here_doc(shell, i);
			if (heredoc_name)
				unlink(heredoc_name);
			i++;
		}
		shell->cmd->redir = shell->cmd->redir->next;
	}
}

void ft_dup(t_shell *shell, t_pipe *pipex, char *command_path)
{
	if (dup_pipe(shell, pipex) == -1)
	{
		printf("error dup_pipe\n");
		free_all(shell, pipex);
		free(command_path);
		exit(1);
	}
	ft_close_fdpipe(pipex);
}

int	dup_pipe(t_shell *shell, t_pipe *pipex)
{
	int	i;
	int	p;

	i = pipex->fdpipe_index;
	p = pipex->pipe_index;
	if (p == FIRST_PIPE)
	{
		if (dup2(pipex->fdpipe[i + 1], STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (p == N_PIPE)
	{
		if (dup2(pipex->fdpipe[i - 2], STDIN_FILENO) == -1)
			return (-1);
		if (shell->fd_out == STDOUT_FILENO)
			if (dup2(pipex->fdpipe[i + 1], STDOUT_FILENO) == -1)
				return (-1);
	}
	else if (p == LAST_PIPE)
	{
		if (dup2(pipex->fdpipe[i], STDIN_FILENO) == -1)
			return (-1);
	}
	return (0);
}

void	ft_dup_redir(t_shell *shell)
{
	if (shell->fd_in != STDIN_FILENO)
	{
		dup2(shell->fd_in, STDIN_FILENO);
		close(shell->fd_in);
	}
	if (shell->fd_out != STDOUT_FILENO)
	{
		dup2(shell->fd_out, STDOUT_FILENO);
		close(shell->fd_out);
	}
}
