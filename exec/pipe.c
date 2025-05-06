#include "minishell.h"

int		ft_wait(pid_t *id_fork, size_t nb_pipes, int wstatus);
void	fork_pipex1(t_token *node, t_pipe *pipex, char **envp);
void	fork_pipex_n(t_token *node, t_pipe *pipex, char **envp);
void	fork_pipex3(t_token *node, t_pipe *pipex, char **envp);

char **recup_command_arg(t_token *node)
{
	char **command_arg;
	char *buffer;
	char *tmp;
	int i;

	i = 0;
	buffer = ft_strdup("");
	if (!buffer)
		return NULL;
	while (node)
	{
		if (*node->is_pipe == 0)
		{
			tmp = buffer;
			buffer = ft_strjoin(buffer, node->tokens);
			if (!buffer)
				return (NULL);
			free(tmp);
			tmp = buffer;
			buffer = ft_strjoin(buffer, " ");
			if (!buffer)
				return (NULL);
			free(tmp);
		}
		else
			break;
		node = node->next;
	}
	command_arg = ft_split(buffer, ' ');
	free(buffer);
	return (command_arg);
}

int ft_pipe(t_token *tokens, char **envp)
{
	t_pipe *pipex;
	size_t nb_pipe = print_pipes_nbr(tokens);
	int	wstatus;
	pid_t id_fork[nb_pipe];
	size_t i;
	size_t j;

	pipex = malloc(sizeof(*pipex));
	if (!pipex)
		return 1;
	pipex->fdpipe = malloc(sizeof(int) * ((nb_pipe * 2) + 1));
	if (pipex->fdpipe == NULL)
		return 1;
	wstatus = 0;
	j = 0;
	pipex->fdpipe[nb_pipe * 2] = 0;
	while (j < nb_pipe * 2)
	{
		if (pipe(((pipex->fdpipe) + j)) == -1)
			free(pipex);
		j += 2;
	}
	id_fork[0] = fork();
	if (id_fork[0] == -1)
	{
		ft_putstr_fd("ERROR ID FORK", 1);
		free(pipex);
		exit(EXIT_FAILURE);
	}
	if (id_fork[0] == 0)
		fork_pipex1(tokens, pipex, envp);
	if (WEXITSTATUS(wstatus) == 127)
		exit(WEXITSTATUS(wstatus));
	i = 1;
	while (i != nb_pipe)
	{
		id_fork[i] = fork();
		if (id_fork[i] == -1)
		{
			ft_putstr_fd("ERROR ID FORK", 1);
			free_struct_pipe(pipex);;
			exit(EXIT_FAILURE);
		}
		while (tokens->count_pipes != i)
			tokens = tokens->next;
		tokens = tokens->next;
		if (id_fork[i] == 0)
			fork_pipex_n(tokens, pipex, envp);
		if (WEXITSTATUS(wstatus) == 127)
			exit(WEXITSTATUS(wstatus));
		i++;
	}
	while (*tokens->is_pipe == 0 && tokens->next != NULL)
		tokens = tokens->next;
	tokens = tokens->next;
	id_fork[nb_pipe] = fork();
	if (id_fork[nb_pipe] == -1)
	{
		ft_putstr_fd("ERROR ID FORK", 1);
		free_struct_pipe(pipex);
		exit(EXIT_FAILURE);
	}
	if (id_fork[nb_pipe] == 0)
	{
		fork_pipex3(tokens, pipex, envp);
	}
	if (WEXITSTATUS(wstatus) == 127)
		exit(WEXITSTATUS(wstatus));
	j = -1;
	while (pipex->fdpipe[++j] != 0)
		close(pipex->fdpipe[j]);
	wstatus = ft_wait(id_fork, nb_pipe, wstatus);
	free_struct_pipe(pipex);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus))
		return (WEXITSTATUS(wstatus));
	return (EXIT_SUCCESS);
}

void	fork_pipex1(t_token *node, t_pipe *pipex, char **envp)
{
	char	*command_path;
	char	**command_arg;

	command_path = check_command_path(node->tokens, envp);
	printf("COMMAND PATH %s\n", command_path);
	command_arg = recup_command_arg(node);
	if (!node->tokens)
	{
		ft_printf("command not found\n");
		exit(1);
	}
	dup2(pipex->fdpipe[1], 1); // besoin d'ecrire dans pipe[1]
	close(pipex->fdpipe[0]); // pas besoin de lire
	close(pipex->fdpipe[1]);
	close(pipex->fdpipe[2]);
	close(pipex->fdpipe[3]); // close fdpipe[1];
	if (execve(command_path, &command_arg[0], envp) == -1)
	{
		ft_putstr_fd("ERROR EXEC VE fork 1", 1);
		free(command_arg);
		free(command_path);
		free_tokens(node);
		free_struct_pipe(pipex);
		exit(127);
	}
}

void	fork_pipex_n(t_token *node, t_pipe* pipex, char **envp)
{
	char	*command_path;
	char	**command_arg;

	command_path = check_command_path(node->tokens, envp);
	printf("COMMAND PATH %s\n", command_path);
	command_arg = recup_command_arg(node);
	if (!node->tokens)
	{
		ft_printf("command not found\n");
		exit(127);
	}
	dup2(pipex->fdpipe[0], 0); //besoin de lire de fdpipe[0]
	dup2(pipex->fdpipe[3], 1); //besoin decrire dans fdpipe[3]
	close(pipex->fdpipe[0]); //close
	close(pipex->fdpipe[1]); //close
	close(pipex->fdpipe[2]); //close
	close(pipex->fdpipe[3]); //close
	if (execve(command_path, &command_arg[0], envp) == -1)
	{
		ft_putstr_fd("ERROR EXEC VE fork 2", 1);
		free(command_arg);
		free(command_path);
		free_tokens(node);
		free_struct_pipe(pipex);
		exit(127);
	}
}

void	fork_pipex3(t_token *node, t_pipe *pipex, char **envp)
{
	char	*command_path;
	char	**command_arg;

	command_path = check_command_path(node->tokens, envp);
	printf("COMMAND PATH %s\n", command_path);
	command_arg = recup_command_arg(node);
	if (!node->tokens)
	{
		ft_printf("command not found\n");
		exit(127);
	}
	dup2(pipex->fdpipe[2], 0); //besoin de lire
	close(pipex->fdpipe[0]); //close fdpipe[0];
	close(pipex->fdpipe[1]); //pas besoin decrire;
	close(pipex->fdpipe[2]); //pas besoin decrire;
	close(pipex->fdpipe[3]); //pas besoin decrire;
	if (execve(command_path, &command_arg[0], envp) == -1)
	{
		perror("ERROR EXEC VE fork3");
		free(command_arg);
		free(command_path);
		free_tokens(node);
		free_struct_pipe(pipex);
		exit(127);
	}
}

int	ft_wait(pid_t *id_fork, size_t nb_pipes, int wstatus)
{
	size_t	i;

	i = 0;
	while (i < nb_pipes + 1)
	{
		if (waitpid(id_fork[i], &wstatus, 0) == -1)
		{
			perror("waitpid error");
			exit(1);
		}
		i++;
	}
	return (wstatus);
}
