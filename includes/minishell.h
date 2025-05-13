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
}			t_pipe;

typedef	enum t_symbol
{
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	APPEND,
}			e_symbol;

typedef struct s_redir
{
	e_symbol		symbol;
	char			*str;
	struct	s_redir *t_redir;
}			t_redir;

typedef struct	s_shell
{
	char			**cmd;
	t_redir			*redir;
	size_t			nb_pipe;
	int				wstatus;
	int				tmp_name_heredoc;
	struct	s_shell *shell;
}				t_shell;

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

void	exec(t_shell *shell, char **envp);
int		exec_cmd(t_shell *node, char **envp);

//pipex_utils
t_pipe	*init_struct_pipex(size_t nb_pipe);
void	pipe_struct_update(t_shell *shell, size_t i);
void	ft_close_fdpipe(t_pipe *pipex);

//REDIRECTIONS
void	open_append_access_outfile(char *str);
void	open_access_outfile(char *str);
void	open_access_infile(char *str);
int 	here_doc(t_shell *shell);

t_shell	*fill_token(t_shell *node, char **arg);

//FREE
void	free_tab(char **tableau);
void	free_params(t_tmp_env *node);
void	free_shell(t_shell *node);
void	free_env(t_envp *node);
void			free_struct_pipe(t_pipe *pipex);
void			free_execve_error(t_shell *tok, t_pipe *p,
					char **c_arg, char *c_path);


t_tmp_env		*create_node_param(void);
t_tmp_env		*add_parameters(char *str, t_tmp_env *node);
char			*find_param(char *command, t_tmp_env *node);
void			ft_add_back(t_tmp_env **lst, t_tmp_env *new);
void			ft_add_front(t_tmp_env **lst, t_tmp_env *new);
t_tmp_env		*ft_last(t_tmp_env *lst);
t_shell			*ft_last_shell(t_shell *lst);
void			print_tab(char **tableau);
void			ft_add_back_shell(t_shell **lst, t_shell *new);
char *get_cmd_arg(t_shell *node, char *buffer);

//built-ins

void	env(char **envp);
void	export(t_shell *shell, char **envp);
int		cd(t_shell *shell, char **envp);
char	*pwd(bool print);
int		ft_exit(t_shell *node);
int		ft_echo(char **tab_cmd, t_tmp_env *node);

void print_shells(t_shell *node);
size_t	print_pipes_nbr(t_shell *node);
char	*recup_env(char **envp);
char	*check_command_path(char *command, char **envp);
char	*new_command_function(char **path, char *new_command);

t_envp	*fill_envp(t_envp *node, char **envp);
t_envp	*ft_last_envp(t_envp *lst);
void	ft_add_back_envp(t_envp **lst, t_envp *new);
t_envp	*create_node_envp(char *env);

bool	is_shell_parameter(t_shell *shell);

t_envp *append_envp(char *arg, char **envp);

void	ft_delone_env(t_envp *lst);
#endif
