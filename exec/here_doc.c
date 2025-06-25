#include "minishell.h"

void	read_heredoc(t_shell *shell, int fd);
int		ft_tmp_open_heredoc(char *name, int i);

char	*here_doc(t_shell *shell, int i)
{
	int		fd;
	char	*name;
	char	*index_tmp;
	char	*limiter;

	index_tmp = ft_itoa(i);
	if (!index_tmp)
		return (false);
	name = ft_strjoin("/tmp/tmp", index_tmp);
	free(index_tmp);
	if (!name)
<<<<<<< Updated upstream:exec/here_doc.c
		return (NULL);
	fd = ft_tmp_open_heredoc(name, i);
	read_heredoc(shell, fd);
	if (shell->cmd->cmd)
		fd = ft_tmp_open_heredoc(name, i);
	if (shell->fd_in > -1)
		close(shell->fd_in);
	shell->fd_in = fd;
	return (name);
}

void	read_heredoc(t_shell *shell, int fd)
=======
		return (false);
	limiter = ft_strdup(cmd->redir->str);
	if (!limiter)
		return (free(name), false);

	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		free(name);
		free(limiter);
		return (false);
	}
	t_redir tmp_redir;
	tmp_redir.str = limiter;

	t_cmd tmp_cmd = *cmd;
	tmp_cmd.redir = &tmp_redir;
	if (!heredoc_wrapper(&tmp_cmd, fd))
	{
		close(fd);
		unlink(name);
		free(name);
		free(limiter);
		return (false);
	}
	free(cmd->redir->str);
	cmd->redir->str = name;
	free(limiter);
	return (true);
}


void	read_heredoc(t_cmd *cmd, int fd)
>>>>>>> Stashed changes:parsing/here_doc.c
{
	char	*word_to_match;
	char	*matching_word;
	size_t	i;

	word_to_match = shell->cmd->redir->str;
	while (1)
	{
		matching_word = readline("> ");
		if (!matching_word)
			break;
		i = 0;
		while (word_to_match[i] || matching_word[i])
		{
			if (word_to_match[i] == matching_word[i])
				i++;
			else
				break;
		}
		if (i == ft_strlen(word_to_match) && matching_word[i] == '\0')
		{
			free(matching_word);
			break;
		}
		ft_putstr_fd(matching_word, fd);
		ft_putchar_fd('\n', fd);
		free(matching_word);
	}
	close(fd);
}

int	ft_tmp_open_heredoc(char *name, int i)
{
	int	fd;

	fd = open(name, O_CREAT | O_RDWR, 0755);
	if (fd == -1)
	{
		printf("ERROR OPENING TMP[%d]", i);
		exit(1);
	}
	return (fd);
}
