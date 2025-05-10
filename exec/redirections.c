#include "minishell.h"

int here_doc(t_token *tokens)
{
	int fd;
	//int tmp_stdout;
	bool exit_while = false;
	char *word_to_match;
	char *matching_word;
	size_t	i;

	tokens = tokens->next;
	word_to_match = tokens->tokens;
	fd = open("tmp", O_CREAT | O_RDWR, 0755 );
	if (fd == -1)
	{
		printf("ERROR OPENING TMP FD");
		exit(1);
	}
	// tmp_stdout = dup(1);
	// if (dup2(fd, 1) == -1 || tmp_stdout == -1)
	// {
	// 	printf("Error dup");
	// 	exit(1);
	// }
	while (!exit_while)
	{
		i = 0;
		matching_word = readline("> ");
		while (word_to_match[i] || matching_word[i])
		{
			if (matching_word[i] == word_to_match[i])
				i++;
			else
				break;
		}
		if (i == ft_strlen(word_to_match) && matching_word[i] == '\0')
			exit_while = true;
		ft_putstr_fd(matching_word, fd);
		ft_putchar_fd('\n', fd);
		free(matching_word);
	}
	// dup2(tmp_stdout, 1);
	// close(tmp_stdout);
	return (fd);
}

int	open_access_infile(char *argv)
{
	int	fd;

	if (access(argv, F_OK) != 0)
	{
		perror("File not accessible");
		exit(EXIT_FAILURE);
	}
	else if (access(argv, R_OK) != 0)
	{
		perror("File not readable");
		exit(EXIT_FAILURE);
	}
	fd = open(argv, O_RDWR);
	if (fd == -1)
	{
		perror("Cannot open file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	open_append_access_outfile(char *argv)
{
	int	fd;

	fd = open(argv, O_CREAT | O_RDWR | O_APPEND, 0755);
	if (fd == -1)
	{
		perror("Cannot open file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	open_access_outfile(char *argv)
{
	int	fd;

	fd = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0755);
	if (fd == -1)
	{
		perror("Cannot open file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

