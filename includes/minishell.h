#pragma once

#include "../LIB_SHELL/lib_shell.h"
#include "execution.h"
#include "parsing.h"

extern char						**environ;

//FREE

void			free_shell(t_shell *node);
void			free_all(t_shell *shell);

//Struct functions

t_envp			*create_node_envp(char *env);
t_envp			*fill_envp(t_envp *node, char **envp);
void			ft_delone_env(t_envp *lst, char *env_to_find);
void			ft_add_back_redir(t_redir **lst, t_redir *new);
void			ft_add_back_envp(t_envp **lst, t_envp *new);
char			**ft_convert_node_to_envp(t_envp *env);
t_envp			*ft_last_envp(t_envp *lst);
char			**ft_convert_node_to_envp(t_envp *env);
bool			find_change_env(t_envp *env, char *new_env, char *target_env);

// Signals

void			set_signals_exec(void);
void			set_signals_interactive(void);
void			set_signals_default(void);
void			heredoc_signal_handler(void);
void			read_heredoc(t_cmd *cmd, int fd);
t_shell			*get_shell_context(t_shell *shell);
