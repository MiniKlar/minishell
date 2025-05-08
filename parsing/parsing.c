#include "minishell.h"

int ft_nb_tokens(char *str)
{
	size_t i;
	size_t k;

	i = 0;
	k = 1;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == ' ')
			k++;
		i++;
	}
	return (k);
}

// void set_caca(char *str, size_t i, t_token *tokens)
// {
// 	size_t k;
// 	size_t j;

// 	j = 0;
// 	k = i - 1;
// 	if (str[k] == ')')
// 	{
// 		while((str[k] != ' ' || str[k + 1] != '(') && k != 0)
// 			k--;
// 	}
// 	else
// 	{
// 		while(str[k] != ' ' && k != 0)
// 			k--;
// 	}
// 	if (strlen(str) == i || k != 0)
// 		k++;
// 	tokens->tokens[tokens->nb_tokens] = malloc(sizeof(char) * (i - k + 1));
// 	while (k != i)
// 	{
// 		tokens->tokens[tokens->nb_tokens][j] = str[k];
// 		j++;
// 		k++;
// 	}
// 	tokens->tokens[tokens->nb_tokens][j] = '\0';
// 	tokens->nb_tokens++;
//}

// void	ft_strtok(t_token *tokens, char *str, char delimiter)
// {
// 	size_t i;
// 	bool parenthesis;

// 	i = 0;
// 	parenthesis = false;
// 	tokens->nb_tokens = 0;
// 	tokens->tokens = malloc(sizeof(char *) * (ft_nb_tokens(str) + 1));
// 	if (!str || !tokens->tokens)
// 		return ;
// 	while (str[i])
// 	{
// 		if (str[i] == '(')
// 			parenthesis = true;
// 		else if (str[i] == delimiter && parenthesis == false)
// 			set_caca(str, i, tokens);
// 		else if (str[i] == ')' && parenthesis == true)
// 		{
// 			parenthesis = false;
// 			i++;
// 			set_caca(str, i, tokens);
// 		}
// 		i++;
// 	}
// 	set_caca(str, i, tokens);
// 	tokens->tokens[tokens->nb_tokens] = NULL;
// }

bool is_shell_parameter(t_token *tokens)
{
	size_t	i;

	i = 0;
	while (tokens->tokens[i] != '\0' && tokens->tokens[i] != '=')
	{
		if (ft_isalpha(tokens->tokens[i]) != 1)
			return (false);
		else
			i++;
	}
	if (ft_strncmp(tokens->tokens, "=", ft_strlen(tokens->tokens)))
		return(true);
	else
		return(false);
}

char *find_param(char *command, t_params *node)
{
	char *tmp;
	command++;
	while (node)
	{
		if (strncmp(node->name, command, ft_strlen(node->name)) == 0)
		{
			tmp = ft_strdup(node->valeur);
			return (tmp);
		}
		else
			node = node->next;
	}
	return (NULL);
}

t_params *create_node_param(void)
{
	t_params	*shell_para;

	shell_para = malloc(sizeof(*shell_para));
	if (!shell_para)
		return (NULL);
	shell_para->name = NULL;
	shell_para->signe = '0';
	shell_para->valeur= NULL;
	shell_para->next=NULL;
	return (shell_para);
}

t_envp *create_node_envp(char *env)
{
	t_envp	*new_env;

	new_env = malloc(sizeof(*new_env));
	if (!new_env)
		return (NULL);
	new_env->envp = ft_strdup(env);
	new_env->next = NULL;
	return (new_env);
}

t_envp *fill_envp(t_envp *node, char **envp)
{
	t_envp *new_node;
	size_t	i;

	i = 0;
	while (envp[i])
	{
		new_node = create_node_envp(envp[i]);
		ft_add_back_envp(&node, new_node);
		i++;
	}
	return (node);
}

void print_tab(char **tableau)
{
	size_t	i;

	i = 0;
	while (tableau[i])
	{
		ft_putstr_fd("Tableau[", 1);
		ft_putchar_fd((i + '0'), 1);
		ft_putstr_fd("] = ", 1);
		ft_putstr_fd(tableau[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}
