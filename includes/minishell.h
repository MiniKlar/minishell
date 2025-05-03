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

typedef struct s_params
{
	char	*name;
	char	signe;
	char	*valeur;
	void	*next;

}			t_params;

void			free_tab(char **tableau);
void			ft_strtok(t_token *tokens, char *str, char delimiter);
t_params		*create_node_param(void);
t_params		*add_parameters(char *str, t_params *node);
char			*find_param(char *command, t_params *node);
void			ft_add_back(t_params **lst, t_params *new);
void			ft_add_front(t_params **lst, t_params *new);
t_params		*ft_last(t_params *lst);
void			free_params(t_params *node);
void			print_tab(char **tableau);

//built-ins

int cd(char *path);
char *pwd(bool print);
int ft_exit(t_params *node);
int ft_echo(char **tab_cmd, t_params *node);
bool is_shell_parameter(char *str);

#endif
