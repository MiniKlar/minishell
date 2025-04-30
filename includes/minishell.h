#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include </usr/include/stdio.h>
#include </usr/include/readline/readline.h>
#include </usr/include/readline/history.h>

typedef struct s_token
{
	char **tokens;
	size_t nb_tokens;
}			t_token;

void	free_tab(char **tab);
void	ft_strtok(t_token *tokens, char *str, char delimiter);

//built-ins

int cd(char *path);
char *pwd(void);
int ft_exit(void);

#endif
