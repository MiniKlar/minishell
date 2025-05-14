#include "minishell.h"

void	read_heredoc(t_shell *shell, int fd);

char	*here_doc(t_shell *shell, int i)
{
	int		fd;
	char	*name;
	name = ft_strjoin("tmp", ft_itoa(i));
	if (!name)
		return (NULL);
	fd = open(name, O_CREAT | O_RDWR, 0755);
	if (fd == -1)
	{
		printf("ERROR OPENING TMP[%d]", i);
		exit(1);
	}
	read_heredoc(shell, fd);
	close(fd);
	fd = open(name, O_CREAT | O_RDWR, 0755);
	if (fd == -1)
	{
		printf("ERROR OPENING TMP[%d]", i);
		exit(1);
	}
	dup2(fd, 0);
	close(fd);
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
			if (matching_word[i] == word_to_match[i])
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
}
