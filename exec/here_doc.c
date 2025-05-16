#include "minishell.h"

void	read_heredoc(t_shell *shell, int fd);
int		ft_tmp_open_heredoc(char *name, int i);
bool	ft_is_last_in(t_shell *shell);

char	*here_doc(t_shell *shell, int i)
{
	int		fd;
	char	*name;

	name = ft_strjoin("/tmp/tmp", ft_itoa(i));
	if (!name)
		return (NULL);
	fd = ft_tmp_open_heredoc(name, i);
	read_heredoc(shell, fd);
	fd = ft_tmp_open_heredoc(name, i);
	if (shell->fd_in != STDIN_FILENO)
	{
		close(shell->fd_in);
		shell->fd_in = fd;
	}
	else
		shell->fd_in = fd;
	return (name);
}

void	read_heredoc(t_shell *shell, int fd)
{
	char	*word_to_match;
	char	*matching_word;
	size_t	i;

	word_to_match = shell->redir->str;
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

bool	ft_is_last_in(t_shell *shell)
{
	t_shell *tmp;

	tmp = shell;
	while (shell->redir->next != NULL)
	{
		if (shell->redir->next->symbol == HERE_DOC
			|| shell->redir->next->symbol == REDIR_IN)
		{
			shell = tmp;
			return (false);
		}
		else
			shell->redir = shell->redir->next;
	}
	shell = tmp;
	return (true);
}
