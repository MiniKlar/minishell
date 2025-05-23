/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:52:35 by lomont            #+#    #+#             */
/*   Updated: 2025/05/23 01:54:26 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <stdio.h>
# include <stdbool.h>

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

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}	t_token;
