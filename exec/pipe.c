#include "minishell.h"

int		ft_wait(pid_t *id_fork, size_t nb_pipes, int wstatus);
void	fork_pipex1(t_token *node, t_pipe *pipex, char **envp);
void	fork_pipex2(t_token *node, t_pipe *pipex, char **envp);
void	fork_pipex3(t_token *node, t_pipe *pipex, char **envp);

char **recup_command_arg(t_token *node)
{
	char *buffer;
	char *tmp;
	char *tmp2;
	char *tmp_str;
	char **command_arg;
	int i;

	i = 0;
	buffer = ft_strdup("");
	if (!buffer)
		return NULL;
	while (node)
	{
		tmp_str = ft_strdup(node->tokens);
		//printf("tmp_str = %s\n", tmp_str);
		if (ft_strncmp(tmp_str, "|", 1) != 0)
		{
			tmp = buffer;
			buffer = ft_strjoin(buffer, node->tokens);
			if (!buffer)
				return (NULL);
			//printf("PREMIER JOIN = %s\n", buffer);
			tmp2 = buffer;
			buffer = ft_strjoin(buffer, " ");
			if (!buffer)
				return (NULL);
			//printf("Deuxieme JOIN = %s\n", buffer);
			free(tmp2);
			free(tmp);
			i++;
		}
		else
		{
			free(tmp_str);
			break;
		}
		free(tmp_str);
		node = node->next;
	}
	//printf("COMMAND_ARG APRES JOIN= %s\n", buffer);
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

	pipex = malloc(sizeof(*pipex));
	if (!pipex)
		return 1;
	wstatus = 0;
	if (pipe(pipex->fdpipe) == -1)
		free(pipex);
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
	while (i <= nb_pipe)
	{
		id_fork[i] = fork();
		if (id_fork[i] == -1)
		{
			ft_putstr_fd("ERROR ID FORK", 1);
			free(pipex);
			exit(EXIT_FAILURE);
		}
		while (tokens->count_pipes != i)
			tokens = tokens->next;
		tokens = tokens->next;
		if (id_fork[i] == 0)
			fork_pipex2(tokens, pipex, envp);
		if (WEXITSTATUS(wstatus) == 127)
			exit(WEXITSTATUS(wstatus));
		i++;
	}
	close(pipex->fdpipe[1]);
	id_fork[nb_pipe] = fork();
	if (id_fork[nb_pipe] == -1)
	{
		ft_putstr_fd("ERROR ID FORK", 1);
		free(pipex);
		exit(EXIT_FAILURE);
	}
	if (id_fork[nb_pipe] == 0)
	{
		printf("TU ES LA BG LETS GO");
		fork_pipex3(tokens, pipex, envp);
	}
	if (WEXITSTATUS(wstatus) == 127)
		exit(WEXITSTATUS(wstatus));
	close(pipex->fdpipe[0]);
	wstatus = ft_wait(id_fork, nb_pipe, wstatus);
	free(pipex);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus))
		return (WEXITSTATUS(wstatus));
	return (EXIT_SUCCESS);
}

void	fork_pipex1(t_token *node, t_pipe *pipex, char **envp)
{
	//char	*command_path;
	char	**command_arg;

	//command_path = check_command_path(node->tokens, envp);
	//printf("COMMAND PATH %s\n", command_path);
	command_arg = recup_command_arg(node);
	printf("%s\n", command_arg[0]);
	printf("%s\n", command_arg[1]);
	//printf("%s\n", command_arg[0]);
	if (!node->tokens)
	{
		ft_printf("command not found\n");
		exit(1);
	}
	close(pipex->fdpipe[0]);
	dup2(pipex->fdpipe[1], 1);
	close(pipex->fdpipe[1]);
	if (execve(node->tokens, &command_arg[0], envp) == -1)
	{
		ft_putstr_fd("ERROR EXEC VE", 1);
		free(command_arg);
		exit(127);
	}
}

void	fork_pipex2(t_token *node, t_pipe* pipex, char **envp)
{
	//char	*command_path;
	char	**command_arg;

	printf("NODE->tokens %s\n", node->tokens);
	//command_path = check_command_path(node->tokens, envp);
	//printf("COMMAND PATH %s\n", command_path);
	command_arg = recup_command_arg(node);
	//printf("%s\n", command_arg[0]);
	if (!node->tokens)
	{
		ft_printf("command not found\n");
		exit(127);
	}
	dup2(pipex->fdpipe[0], 0);
	dup2(pipex->fdpipe[1], 1);
	close(pipex->fdpipe[0]);
	close(pipex->fdpipe[1]);
	if (execve(node->tokens, &command_arg[0], envp) == -1)
	{
		ft_putstr_fd("ERROR EXEC VE", 1);
		free(command_arg);
		exit(127);
	}
}

void	fork_pipex3(t_token *node, t_pipe *pipex, char **envp)
{
//	char	*command_path;
	char	**command_arg;

	printf("NODE->tokens %s\n", node->tokens);
	//command_path = check_command_path(node->tokens, envp);
	//printf("COMMAND PATH %s\n", command_path);
	command_arg = recup_command_arg(node);
	if (!node->tokens)
	{
		ft_printf("command not found\n");
		exit(127);
	}
	dup2(pipex->fdpipe[0], 0);
	close(pipex->fdpipe[0]);
	close(pipex->fdpipe[1]);
	if (execve(node->tokens, &command_arg[0], envp) == -1)
	{
		ft_putstr_fd("ERROR EXEC VE", 1);
		free(command_arg);
		exit(127);
	}
}

int	ft_wait(pid_t *id_fork, size_t nb_pipes, int wstatus)
{
	size_t i;

	i = 0;
	while (i < nb_pipes)
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
