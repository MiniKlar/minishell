#pragma once

#include "../LIB_SHELL/lib_shell.h"
#include "execution.h"
#include "parsing.h"

//MAIN FUNCTIONS

bool			is_cmd_built_ins(t_shell *shell);
void			exec(t_shell *shell);
int				exec_cmd(t_shell *shell);
int				exec_built_in(t_shell *shell, bool is_child);
int				ft_wait(t_shell *shell, pid_t *id_fork, size_t nb_pipes);
char			*find_command_exist_executable(t_shell *shell, t_pipe *pipex, pid_t *id);

//pipex_utils

t_pipe			*init_struct_pipex(void);
t_pipe			*set_struct_pipex(t_shell *shell);
void			pipe_struct_update(t_shell *shell, t_pipe *pipex, size_t i);

char			*check_command_path(char *command, char **envp);
char			*recup_env(char **envp);
char			*new_command_function(char **path, char *new_command);

//REDIRECTIONS

void			redir_outfile(t_shell *shell);
void			redir_infile(t_shell *shell);
char 			*here_doc(t_shell *shell, int i);
bool			ft_is_last_fd_in(t_shell *shell);
void			redir_cmd_input_output(t_shell *shell);
void			ft_dup_redir(t_shell *shell);

//FREE

void			free_shell(t_shell *node);
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
t_envp			*ft_last_envp(t_envp *lst);

