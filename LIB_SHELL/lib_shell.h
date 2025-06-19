/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_shell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:57:19 by lomont            #+#    #+#             */
/*   Updated: 2025/06/17 01:06:48 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "struct.h"
# include <curses.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>
//# include <signal.h>
# include <unistd.h>
# include <term.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

// IS FUNCTIONS

int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isprint(int c);
int			ft_isascii(int c);
int			ft_isspace(int c);
int			ft_isnegative(long c);

// MEM FUNCTIONS

void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);

int			ft_memcmp(const void *s1, const void *s2, size_t n);

// PUT FUNCTIONS

void		ft_putnbr_fd(int n, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);

// CONVERT FUNCTIONS

char		*ft_lltoa(long long n);
char		*ft_itoa(int n);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_atoi(const char *str);
long		ft_atol(const char *str);
long long	ft_atoll(const char *str);

// STR FUNCTIONS

size_t		ft_strlen(const char *string);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);

char		*ft_strdup(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		**ft_split(const char *s, char c);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char		*ft_strnstr(const char *big, const char *little, size_t len);

void		ft_striteri(char *s, void (*f)(unsigned int, char*));

int			ft_strncmp(const char *s1, const char *s2, size_t n);

// STRUCTS FUNCTIONS

void		token_add_back(t_token **head, t_token *new);
void		redir_add_back(t_redir **head, t_redir *new);
void		cmd_add_back(t_cmd **head, t_cmd *new);
t_cmd		*add_cmd_to_shell(t_shell *shell, char **cmd_args);
bool		add_redir_to_cmd(t_cmd *cmd, char *str, t_symbol symbol);

// ENVP STRUCT FUNCTIONS

char		**ft_malloc_envp(char **envp);
t_envp		*create_node_envp(char *env);
t_envp		*fill_envp(t_envp *node, char **envp);
void		ft_add_back_envp(t_envp **lst, t_envp *new);
t_envp		*ft_last_envp(t_envp *lst);

// REDIR STRUCT FUNCTIONS

t_redir			*create_node_redir(char *arg);
t_redir			*create_node_redir_out(char *arg);
t_redir			*create_node_here_redir(char *arg);

// INIT FUNCTION

t_cmd		*init_cmd(char **cmd_args);
t_redir		*init_redir(char *str, t_symbol symbol);
t_token		*init_token(char *value);
t_shell		*init_shell(char **envp);

// SHELL FUNCTIONS

size_t		get_cmd_count(t_cmd *cmd);
char		*get_env_value(char *name, char **envp);
char		*extract_env_name(char *var);

// FREE FUNCTIONS

void		free_array(char **array);
void		free_cmd_struct(t_cmd *cmd);
void		free_redir_struct(t_redir *redir);
void		free_shell(t_shell *shell);
void		free_token_struct(t_token *token);
void		free_env(t_envp *env);

// GET_NEXT_LINE

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char		*get_next_line(int fd);

// PRINTF

void		print_array(char **array);
int			ft_print_nbr(int n);
int			ft_print_str(char *s);
int			ft_print_char(char c);
int			ft_print_hexaptr(void *n);
int			ft_put_unsigned(unsigned int n);
int			ft_puthexa_upper(unsigned int n);
int			ft_puthexa_lower(unsigned int n);
int			ft_printf(const char *string, ...);
int			ft_puthexa_ptr(unsigned long address);
