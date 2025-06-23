#include "parsing.h"

void	read_heredoc(t_cmd *cmd, int fd);

bool	here_doc(t_cmd *cmd, int i)
{
	int		fd;
	char	*name;
	char	*index_tmp;

	index_tmp = ft_itoa(i);
	name = ft_strjoin("/tmp/tmp", index_tmp);
	free(index_tmp);
	if (!name)
		return (false);
	fd = open(name, O_CREAT | O_RDWR, 0755);
	if (fd == -1)
	{
		printf("Error when trying to open/create tmpfile %s", name);
		free(name);
		return (false);
	}
	read_heredoc(cmd, fd);
	if (cmd->redir->str != NULL)
	{
		unlink(cmd->redir->str);
		free(cmd->redir->str);
	}
	cmd->redir->str = name;
	return (true);
}

void	read_heredoc(t_cmd *cmd, int fd)
{
	char	*word_to_match;
	char	*matching_word;
	size_t	i;

	word_to_match = cmd->redir->str;
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

bool	ft_tmp_open_heredoc(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->redir->str, O_RDWR);
	if (fd == -1)
	{
		printf("Error opening %s", cmd->redir->str);
		return (false);
	}
	if (cmd->fd_in > -1)
		close(cmd->fd_in);
	cmd->fd_in = fd;
	return (true);
}
