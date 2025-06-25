#include "parsing.h"

bool	read_heredoc(t_cmd *cmd, int fd);

bool	here_doc(t_cmd *cmd, int i)
{
	int		fd;
	char	*name;
	char	*index_tmp;

	index_tmp = ft_itoa(i);
	if (!index_tmp)
		return (NULL);
	name = ft_strjoin("/tmp/tmp", index_tmp);
	free(index_tmp);
	if (!name)
		return (false);
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open"), free(name), false);
	if (!read_heredoc(cmd, fd))
		return (free(name), false);
	if (cmd->redir->str != NULL)
	{
		unlink(cmd->redir->str);
		free(cmd->redir->str);
	}
	cmd->redir->str = name;
	return (true);
}

bool	read_heredoc(t_cmd *cmd, int fd)
{
	char	*word_to_match;
	char	*word;

	word_to_match = cmd->redir->str;
	set_signals_heredoc();
	while (1)
	{
		ft_putstr_fd("> ", 1);
		word = get_next_line(STDIN_FILENO);
		if (!word)
		{
			if (g_sig == 2)
			{
				ft_putstr_fd("bash: here-doc terminated by signal\n", 2);
				return (close(fd), false);
			}
			else
				break ;
		}
		if (ft_strncmp(word_to_match, word, ft_strlen(word) - 1) == 0
			&& (ft_strlen(word) - 1 == ft_strlen(word_to_match)))
			break ;
		ft_putstr_fd(word, fd);
		free(word);
	}
	while (get_next_line(STDIN_FILENO) != NULL)
		get_next_line(STDIN_FILENO);
	return (free(word), close(fd), true);
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
