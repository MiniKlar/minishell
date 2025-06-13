#pragma once

# define FIRST_PIPE		1
# define N_PIPE			2
# define LAST_PIPE		3

//MAIN FUNCTIONS

bool			is_cmd_built_ins(t_shell *shell);
void			exec(t_shell *shell);
int				exec_cmd(t_shell *shell);
bool			exec_built_in(t_shell *shell, bool is_child);
int				ft_wait(t_shell *shell, size_t nb_pipes);
char			*find_command_exist_executable(t_shell *shell);

//pipex_utils

t_pipe			*init_struct_pipex(void);
t_pipe			*set_struct_pipex(t_shell *shell);
void			pipe_struct_update(t_shell *shell, size_t i);

char			*check_command_path(char *command, char **envp);
char			*recup_env(char **envp);
char			*new_command_function(char **path, char *new_command);

//REDIRECTIONS

void			redir_outfile(t_shell *shell);
void			redir_infile(t_shell *shell);
char 			*here_doc(t_shell *shell, int i);
void			redir_cmd_input_output(t_shell *shell);
void			ft_dup_redir(t_shell *shell, bool is_child);
void			ft_dup_std(t_shell *shell);
void			ft_dup_std_back(t_shell *shell);
void			ft_dup(t_shell *shell, char *command_path);

//built-ins

int				ft_env(t_shell *shell);
void			ft_exit(t_shell *shell);
int				ft_cd(t_shell *shell);
int				ft_pwd(bool print);
int				ft_echo(t_shell *shell);
int				ft_unset(t_shell *shell);
int				ft_export(t_shell *shell);

//Signal
// void set_signal_action(void);
// void sig_handler(int signal);
