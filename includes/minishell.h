#ifndef MINISHELL_H
# define MINISHELL_H

#include "../LIB_C/LIB_C.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_token
{
	char **tokens;
	size_t nb_tokens;
}			t_token;

typedef struct s_parameters
{
	char	*name;
	char	signe;
	char	*valeur;

}			t_parameters;

void			free_tab(char **tableau);
void			ft_strtok(t_token *tokens, char *str, char delimiter);
t_parameters	*create_node_param(void);
t_parameters	*add_parameters(char *str);
char			*find_param(char *command, t_parameters *node);

//built-ins

int cd(char *path);
char *pwd(bool print);
int ft_exit(void);
int ft_echo(char **tab_cmd, t_parameters *node);
bool is_shell_parameter(char *str);

#endif
