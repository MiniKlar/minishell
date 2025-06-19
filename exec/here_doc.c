#include "minishell.h"

void	read_heredoc(t_shell *shell, int fd);
int		ft_tmp_open_heredoc(char *name, int i);

char	*here_doc(t_shell *shell, int i)
{
	int		fd;
	char	*name;
	char	*index_tmp;

	index_tmp = ft_itoa(i);
	name = ft_strjoin("/tmp/tmp", index_tmp);
	free(index_tmp);
	if (!name)
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
{
	char	*word_to_match;
	char	*matching_word;
	size_t	i;

	word_to_match = shell->cmd->redir->str;
	while (1)
	{
		i = 0;
		matching_word = readline("> ");
		while (word_to_match[i] || matching_word[i])
		{
			if (word_to_match[i] == matching_word[i])
				i++;
			else
				break ;
		}
		if (i == ft_strlen(word_to_match) && matching_word[i] == '\0')
			break ;
		ft_putstr_fd(matching_word, fd);
		ft_putchar_fd('\n', fd);
		free(matching_word);
	}
	free(matching_word);
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
