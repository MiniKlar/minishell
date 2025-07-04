/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:57:48 by lomont            #+#    #+#             */
/*   Updated: 2025/06/25 12:57:50 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <dirent.h>

#define FIRST_PIPE		1
#define N_PIPE			2
#define LAST_PIPE		3

//MAIN FUNCTIONS

bool			is_cmd_built_ins(t_shell *shell);
void			exec(t_shell *shell);
int				exec_cmd(t_shell *shell);
bool			exec_built_in(t_shell *shell, bool is_child);
int				ft_wait(t_shell *shell, size_t nb_pipes, int *wstatus);
char			*find_command_exist_executable(t_shell *shell);
void			free_child(t_shell *shell, char *command_path);
void			create_children(t_shell *shell);
void			create_child(t_shell *shell);
void			check_redir(t_shell *shell, char *command_path);

//pipex_utils

t_pipe			*init_struct_pipex(void);
t_pipe			*set_struct_pipex(t_shell *shell);
void			pipe_struct_update(t_shell *shell, size_t i);

char			*check_command_path(char *command, char **envp);
char			*recup_env(char **envp);
char			*new_command_function(char **path, char *new_command);

//REDIRECTIONS

void			ft_dup_redir(t_shell *shell, bool is_child);
void			ft_dup_std(t_shell *shell);
void			ft_dup_std_back(t_shell *shell);
void			ft_dup(t_shell *shell, char *command_path);
bool			ft_tmp_open_heredoc(t_cmd *cmd);

//built-ins

int				ft_env(t_shell *shell);
void			ft_exit(t_shell *shell);
int				ft_cd(t_shell *shell);
int				ft_pwd(t_shell *shell, bool print);
int				ft_echo(t_shell *shell);
int				ft_unset(t_shell *shell);
int				ft_export(t_shell *shell);

//built-ins utils
char			*gethome_without_env(void);
bool			check_has_options(char *arg, char *cmd);
void			print_error(char *str);
void			exit_status_free(t_shell *shell, int code);

//Directory
bool			check_if_directory(t_shell *shell);
