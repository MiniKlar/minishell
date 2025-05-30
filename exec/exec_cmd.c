#include "minishell.h"

void	create_child(t_shell *shell, t_pipe *pipex, pid_t *id_fork);
void	create_children(t_shell *shell, pid_t *id_fork, t_pipe *pipex);
int		ft_wait(t_shell *shell, pid_t *id_fork, size_t nb_pipes);
pid_t	*fork_cmd(t_shell *shell, t_pipe *pipex);
void	redir_cmd_input_output(t_shell *shell);
int		dup_pipe(t_shell *shell, t_pipe *pipex);
void	ft_dup(t_shell *shell, t_pipe *pipex, char *command_path);
void	ft_dup_redir(t_shell *shell);

int	exec_cmd(t_shell *shell)
{
	t_pipe	*pipex;		//déclaration de ma struct pipex pour stocker données pour mes pipes.
	pid_t	*id_fork;	//déclaration init_fork pour stocker les pids de mes enfants.

	if (shell->nb_pipe != 0)	//si le nombre de pipe est à 0 (donc je n'ai qu'un child a créer)
		pipex = set_struct_pipex(shell);	//alors je remplis ma structure
	else
		pipex = NULL;	//sinon pipex init a NULL
	id_fork = fork_cmd(shell, pipex); //init du nombres d'enfants
	shell->wstatus = ft_wait(shell, id_fork, shell->nb_pipe);
	if (WIFEXITED(shell->wstatus) && WEXITSTATUS(shell->wstatus))
	{
		free(pipex);
		free(id_fork);
		return (WEXITSTATUS(shell->wstatus));
	}
	free(pipex);
	free(id_fork);
	return (0);
}

pid_t	*fork_cmd(t_shell *shell, t_pipe *pipex)
{
	size_t	nb_fork;
	pid_t	*id_fork;

	if (shell->nb_pipe == 0) //si nb_pipe = 0
		nb_fork = 1;	//alors nb enfant = 1
	else
		nb_fork = shell->nb_pipe + 1; //sinon nb enfant = nb pipe + 1 = nb commande
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
	t_cmd	*tmp;

	i = 0; //init a 0 index.
	tmp = shell->cmd;
	while (shell->cmd != NULL) //tant qu'il y a des commandes
	{
		if (shell->nb_pipe > 0)
		{
			if (pipe(pipex->fdpipe) == -1)
			{
				free(id_fork);
				free_all(shell, pipex);
				exit(EXIT_FAILURE);
			}
		}
		id_fork[i] = fork();	//on fork puis on met dans la variable id_fork le numero de lenfant
		if (id_fork[i] == -1) //si ca echoue
		{
			printf("Error fork id_fork[%zu]", i);
			free(id_fork);
			free_all(shell, pipex); //on free tout
		}
		else if (id_fork[i] == 0) //si c'est 0
			create_child(shell, pipex, id_fork); //on cree lenfant
		if (shell->nb_pipe > 0)
			pipe_struct_update(shell, pipex, i); //on met a jour la struct pipe pour la prochaine commande.
		shell->cmd = shell->cmd->next; //on avant dans les commandes.
		i++; //on avance dans l'index des id fork.
	}
	shell->cmd = tmp;
}

void	create_child(t_shell *shell, t_pipe *pipex, pid_t *id_fork)
{
	char	*command_path; //on initialise la string pour placer notre path de commande
	bool	is_built_ins;	//on crée un boolean pour savoir si cest un built in

	is_built_ins = is_cmd_built_ins(shell);	//on check si cest un builtin
	if (!is_built_ins) //si ce nest pas un built in
		command_path = find_command_exist_executable(shell, pipex, id_fork); //on va check la commande si elle existe
	redir_cmd_input_output(shell); //redirection in et out (infile, outfile, heredoc)
	ft_dup_redir(shell); //dup le fd_in et fd_out
	if (shell->nb_pipe != 0) //si il y a des pipes
		ft_dup(shell, pipex, command_path); //dup les pipes
	if (is_built_ins) //si cest un built in
	{
		exec_built_in(shell); //exec built in
		exit(shell->wstatus); // exit wstatus
	}
	else if (execve(command_path, &shell->cmd->cmd[0], shell->envp) == -1) //sinon execve
	{
		perror("ERROR EXEC VE");
		free(id_fork);
		free_all(shell, pipex);
		free(command_path);
		exit(126);
	}
}

void	redir_cmd_input_output(t_shell *shell)
{
	char		*heredoc_name;
	t_symbol	type_redir;
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
	if (pipex->in_fd != -1)
		close(pipex->in_fd);
	close(pipex->fdpipe[0]);
	close(pipex->fdpipe[1]);
}

int	dup_pipe(t_shell *shell, t_pipe *pipex)
{
	int	p;

	p = pipex->pipe_index;
	if (p == FIRST_PIPE)
	{
		if (dup2(pipex->fdpipe[1], STDOUT_FILENO) == -1) //peut etre changer pour eviter que ca ecrive pipe[1] si redir avant
			return (-1);
	}
	else if (p == N_PIPE)
	{
		if (shell->fd_in == STDIN_FILENO)
			if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
				return (-1);
		if (shell->fd_out == STDOUT_FILENO)
			if (dup2(pipex->fdpipe[1], STDOUT_FILENO) == -1)
				return (-1);
	}
	else if (p == LAST_PIPE)
	{
		if (dup2(pipex->in_fd, STDIN_FILENO) == -1) //peut etre changer pour eviter que ca lise pipe[0] si redir avant
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
