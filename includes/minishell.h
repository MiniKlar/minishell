#pragma once

#include "../LIB_SHELL/lib_shell.h"
#include "execution.h"
#include "parsing.h"

extern char						**environ;
extern volatile sig_atomic_t	g_sig;

//FREE

void			free_shell(t_shell *node);
void			free_all(t_shell *shell);
void			free_eof(t_shell *shell);

//UTILS FUNCTIONS

char			*remove_char_arg(char *arg);
char			*remove_extra_char_before_egal(char *arg);
bool			check_arg_export_syntax(char *arg);
bool			error_export(char *arg, int error_code);
void			export_all(char **envp);
void			create_fdpipe(t_shell *shell);
int				dup_pipe(t_shell *shell);
bool			built_ins_1(t_shell *shell);
bool			built_ins_2(t_shell *shell);
bool			is_cmd_built_ins(t_shell *shell);

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

void			set_signals_interactive(void);
void			ignore_sigint(void);
void			set_signals_child(void);
void			set_signals_heredoc(void);
