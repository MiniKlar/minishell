#include "minishell.h"

void	read_heredoc(t_shell *shell, int fd);

void	here_doc(t_shell *shell)
{
	int		fd;
	char	*name;

	name = ft_strjoin("tmp", shell->tmp_name_heredoc + "0");
	if (!name)
		return (NULL);
	fd = open(name, O_CREAT | O_RDWR, 0755);
	if (fd == -1)
	{
		printf("ERROR OPENING TMP FD");
		exit(1);
	}
	read_heredoc(shell, fd);
	dup2(fd, 0);
	close(fd);
}

void	read_heredoc(t_shell *shell, int fd)
{
	char	*word_to_match;
	char	*matching_word;
	bool	exit_while;
	size_t	i;

	exit_while = false;
	word_to_match = shell->redir->str;
	while (!exit_while)
	{
		i = 0;
		matching_word = readline("> ");
		while (word_to_match[i] || matching_word[i])
		{
			if (matching_word[i] == word_to_match[i])
				i++;
			else
				break ;
		}
		if (i == ft_strlen(word_to_match) && matching_word[i] == '\0')
			exit_while = true;
		ft_putstr_fd(matching_word, fd);
		ft_putchar_fd('\n', fd);
		free(matching_word);
	}
}
