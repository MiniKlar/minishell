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
	char	**envp;
	char	*tokens;
	size_t	nb_tokens;
	size_t	count_pipes;
	bool	is_pipe;
	void	*next;
}			t_token;

typedef struct s_tmp_env
{
	char	*name;
	char	signe;
	char	*valeur;
	void	*next;

}			t_tmp_env;

typedef struct s_envp
{
	char *envp;
	void *next;
}			t_envp;

t_token			*fill_token(t_token *node, char**arg);
void			free_tab(char **tableau);
void			ft_strtok(t_token *tokens, char *str, char delimiter);
t_tmp_env		*create_node_param(void);
t_tmp_env		*add_parameters(char *str, t_tmp_env *node);
char			*find_param(char *command, t_tmp_env *node);
void			ft_add_back(t_tmp_env **lst, t_tmp_env *new);
void			ft_add_front(t_tmp_env **lst, t_tmp_env *new);
t_tmp_env		*ft_last(t_tmp_env *lst);
t_token			*ft_last_token(t_token *lst);
void			free_params(t_tmp_env *node);
void			print_tab(char **tableau);
void			ft_add_back_tokens(t_token **lst, t_token *new);
void			free_struct_pipe(t_pipe *pipex);
void			free_execve_error(t_token *tok, t_pipe *p,
					char **c_arg, char *c_path);
char *get_cmd_arg(t_token *node, char *buffer);

//built-ins

int cd(t_token *tokens, char **envp);
char *pwd(bool print);
int ft_exit(t_token *node);
int ft_echo(char **tab_cmd, t_tmp_env *node);
size_t print_pipes_nbr(t_token *node);
void	free_tokens(t_token *node);
void print_tokens(t_token *node);

char	*recup_env(char **envp);
char	*check_command_path(char *command, char **envp);
char	*new_command_function(char **path, char *new_command);
int		ft_pipe(t_token *node, char**envp);
void	exec_cmd(t_token *tokens, char **envp);

char	**recup_command_arg(t_token *node);
t_envp	*fill_envp(t_envp *node, char **envp);
t_envp	*ft_last_envp(t_envp *lst);
void	ft_add_back_envp(t_envp **lst, t_envp *new);
t_envp	*create_node_envp(char *env);

bool	is_shell_parameter(t_token *tokens);
void	export(t_token *tokens, char **envp);
t_envp *append_envp(t_token *tokens, char **envp);
void	free_env(t_envp *node);
void env(char **envp);
void	ft_delone_env(t_envp *lst);
#endif
