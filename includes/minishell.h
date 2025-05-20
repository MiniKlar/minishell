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

# ifndef FIRST_PIPE
	# define FIRST_PIPE		1
# endif
# ifndef N_PIPE
	# define N_PIPE			2
# endif
# ifndef LAST_PIPE
	# define LAST_PIPE		3
# endif

typedef struct 	s_pipe
{
	int			*fdpipe;
	int			*fdpipe2;
	int			fdpipe_index;
	int			pipe_index;
}				t_pipe;

typedef	enum 	t_symbol
{
				REDIR_IN,
				REDIR_OUT,
				HERE_DOC,
				APPEND,
}				e_symbol;

typedef struct 	s_redir
{
	e_symbol		symbol;
	char			*str;
	struct	s_redir *next;
}				t_redir;

typedef struct 	s_cmd
{
	char 			**cmd;
	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_shell
{
	char		**envp;
	t_cmd		*cmd;
	size_t		nb_pipe;
	int			fd_in;
	int			fd_out;
	int			wstatus;
}				t_shell;

typedef struct s_envp
{
	char 		*envp;
	void 		*next;
}				t_envp;

//MAIN FUNCTIONS

bool			exec_built_in_inside_child(t_shell *shell);
bool			is_cmd_built_ins(t_shell *shell);
void			exec(t_shell *shell);
int				exec_cmd(t_shell *shell);
int				exec_built_in(t_shell *shell);
int				ft_wait(t_shell *shell, pid_t *id_fork, size_t nb_pipes);
char			**ft_malloc_envp(char **envp);
char			*find_command_exist_executable(t_shell *shell, t_pipe *pipex);

//pipex_utils

t_pipe			*init_struct_pipex(size_t nb_pipe);
t_pipe			*set_struct_pipex(t_shell *shell);
char			*check_command_path(char *command, char **envp);
void			ft_close_fdpipe(t_pipe *pipex);
void			pipe_struct_update(t_shell *shell, t_pipe *pipex, size_t i);

char			*recup_env(char **envp);
char			*new_command_function(char **path, char *new_command);

//REDIRECTIONS

void			redir_outfile(t_shell *shell);
void			redir_infile(t_shell *shell);
char 			*here_doc(t_shell *shell, int i);
bool			ft_is_last_fd_in(t_shell *shell);

//FREE

void			free_shell(t_shell *node);
void			free_struct_pipe(t_pipe *pipex);
void			free_all(t_shell *shell, t_pipe *pipex);

//built-ins

int				ft_env(t_shell *shell);
void			ft_exit(t_shell *shell);
int				ft_cd(t_shell *shell);
int				ft_pwd(bool print);
int				ft_echo(t_shell *shell);
int				ft_unset(t_shell *shell);
int				ft_export(t_shell *shell);

//Struct functions

t_envp			*create_node_envp(char *env);
t_envp			*fill_envp(t_envp *node, char **envp);
t_redir			*create_node_redir(char *arg);
t_redir			*create_node_redir_out(char *arg);
t_redir			*create_node_here_redir(char *arg);
void			ft_delone_env(t_envp *lst, char *env_to_find);
void			ft_add_back_redir(t_redir **lst, t_redir *new);
void			ft_add_back_envp(t_envp **lst, t_envp *new);
char			**ft_convert_node_to_envp(t_envp *env);

#endif
