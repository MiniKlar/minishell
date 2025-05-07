#ifndef MINISHELL_H
# define MINISHELL_H

#include "../LIB_C/LIB_C.h"
#include <sys/stat.h>
#include <sys/wait.h>
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

# define FIRST_PIPE		1
# define N_PIPE			2
# define LAST_PIPE		3

typedef struct s_pipe
{
	int		*fdpipe;
	int		fdpipe_index;
	int		pipe_index;
	int		wstatus;
	size_t	nb_pipe;
}			t_pipe;

typedef struct s_token
{
	char	*tokens;
	size_t	nb_tokens;
	size_t	count_pipes;
	bool	is_pipe;
	void	*next;
}			t_token;

typedef struct s_params
{
	char	*name;
	char	signe;
	char	*valeur;
	void	*next;

}			t_params;

t_token			*fill_token(t_token *node, char**arg);
void			free_tab(char **tableau);
void			ft_strtok(t_token *tokens, char *str, char delimiter);
t_params		*create_node_param(void);
t_params		*add_parameters(char *str, t_params *node);
char			*find_param(char *command, t_params *node);
void			ft_add_back(t_params **lst, t_params *new);
void			ft_add_front(t_params **lst, t_params *new);
t_params		*ft_last(t_params *lst);
t_token			*ft_last_token(t_token *lst);
void			free_params(t_params *node);
void			print_tab(char **tableau);
void			ft_add_back_tokens(t_token **lst, t_token *new);
void			free_struct_pipe(t_pipe *pipex);
void			free_execve_error(t_token *tok, t_pipe *p,
					char **c_arg, char *c_path);
char *get_cmd_arg(t_token *node, char *buffer);

//built-ins

int cd(char *path);
char *pwd(bool print);
int ft_exit(t_params *node);
int ft_echo(char **tab_cmd, t_params *node);
bool is_shell_parameter(char *str);
size_t print_pipes_nbr(t_token *node);
void	free_tokens(t_token *node);
void print_tokens(t_token *node);

char	*recup_env(char **envp);
char	*check_command_path(char *command, char **envp);
char	*new_command_function(char **path, char *new_command);
int ft_pipe(t_token *node, char**envp);

char **recup_command_arg(t_token *node);

#endif
