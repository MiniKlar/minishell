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
		if (node->is_pipe == false)
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
		return (EXIT_FAILURE);
	pipex->fdpipe = malloc(sizeof(int) * ((nb_pipe * 2) + 1));
	if (pipex->fdpipe == NULL)
	{
		free(pipex);
		return (EXIT_FAILURE);
	}
	wstatus = 0;
	j = 0;
	pipex->fdpipe[nb_pipe * 2] = 0;
	while (j < nb_pipe * 2)
	{
		if (pipe(((pipex->fdpipe) + j)) == -1)
		{
			perror("Error pipe");
			free(pipex);
			return (EXIT_FAILURE);
		}
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
	while (tokens->is_pipe == false && tokens->next != NULL)
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
		fork_pipex3(tokens, pipex, envp);
	if (WEXITSTATUS(wstatus) == 127)
		exit(WEXITSTATUS(wstatus));
	j = 0;
	while (pipex->fdpipe[j] != 0)
	{
		close(pipex->fdpipe[j]);
		j++;
	}
	wstatus = ft_wait(id_fork, nb_pipe, wstatus);
	free_struct_pipe(pipex);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus))
		return (WEXITSTATUS(wstatus));
	return (EXIT_SUCCESS);
}

void	fork_pipex1(t_token *node, t_pipe *pipex, char **envp)
{
	char	**command_arg;
	char	*command_path;
	size_t	i;

	i = 0;
	command_path = check_command_path(node->tokens, envp);
	command_arg = recup_command_arg(node);
	if (dup2(pipex->fdpipe[i + 1], 1) == -1)
	{
		free_execve_error(node, pipex, command_arg, command_path);
		exit(1);
	}
	while (pipex->fdpipe[i] != 0)
	{
		printf("valeur de i = %zu\n", i);
		close(pipex->fdpipe[i]);
		i++;
	}
	if (execve(command_path, &command_arg[0], envp) == -1)
	{
		perror("ERROR EXEC VE fork 1");
		free_execve_error(node, pipex, command_arg, command_path);
		exit(127);
	}
}

void	fork_pipex_n(t_token *node, t_pipe* pipex, char **envp)
{
	char	**command_arg;
	char	*command_path;
	size_t	i;

	i = 0;
	command_path = check_command_path(node->tokens, envp);
	if (!command_path)
	{
		ft_putstr_fd("command_path NULL",2);
		exit(1);
	}
	command_arg = recup_command_arg(node);
	if (dup2(pipex->fdpipe[0], 0) == -1 || dup2(pipex->fdpipe[3], 1) == -1)
	{
		free_execve_error(node, pipex, command_arg, command_path);
		exit(1);
	}
	while (pipex->fdpipe[i] != 0)
	{
		close(pipex->fdpipe[i]);
		i++;
	}
	if (execve(command_path, &command_arg[0], envp) == -1)
	{
		perror("ERROR EXEC VE fork");
		free_execve_error(node, pipex, command_arg, command_path);
		exit(127);
	}
}

void	fork_pipex3(t_token *node, t_pipe *pipex, char **envp)
{
	char	**command_arg;
	char	*command_path;
	size_t	i;

	i = 0;
	command_path = check_command_path(node->tokens, envp);
	if (!command_path)
	{
		ft_putstr_fd("command_path NULL",2);
		exit(1);
	}
	command_arg = recup_command_arg(node);
	while (pipex->fdpipe[i] != 0)
		i++;
	if (dup2(pipex->fdpipe[i - 2], 0) == -1)
	{
		free_execve_error(node, pipex, command_arg, command_path);
		exit(-1);
	}
	i = 0;
	while (pipex->fdpipe[i] != 0)
	{
		close(pipex->fdpipe[i]);
		i++;
	}
	if (execve(command_path, &command_arg[0], envp) == -1)
	{
		perror("ERROR EXEC VE fork3");
		free_execve_error(node, pipex, command_arg, command_path);
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
