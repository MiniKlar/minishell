/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:52:35 by lomont            #+#    #+#             */
/*   Updated: 2025/06/07 00:48:29 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct 	s_pipe
{
	int			fdpipe[2];
	int			in_fd;
	int			fdpipe_index;
	int			pipe_index;
}				t_pipe;

typedef enum s_symbol
{
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	APPEND
}	t_symbol;

typedef struct 	s_redir
{
	t_symbol		symbol;
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
	t_cmd		*first_cmd;
	t_cmd		*cmd;
	t_pipe		*pipex;
	pid_t		*id_fork;
	size_t		nb_pipe;
	bool		is_child;
	int			tmp_stdin;
	int			tmp_stdout;
	int			fd_in;
	int			fd_out;
	int			wstatus;
}				t_shell;

typedef struct s_envp
{
	char 		*envp;
	void 		*next;
}				t_envp;

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}	t_token;
