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

void set_caca(char *str, size_t i, t_token *tokens)
{
	size_t k;
	size_t j;

	j = 0;
	k = i - 1;
	if (str[k] == ')')
	{
		while((str[k] != ' ' || str[k + 1] != '(') && k != 0)
			k--;
	}
	else
	{
		while(str[k] != ' ' && k != 0)
			k--;
	}
	if (strlen(str) == i || k != 0)
		k++;
	tokens->tokens[tokens->nb_tokens] = malloc(sizeof(char) * (i - k + 1));
	while (k != i)
	{
		tokens->tokens[tokens->nb_tokens][j] = str[k];
		j++;
		k++;
	}
	tokens->tokens[tokens->nb_tokens][j] = '\0';
	tokens->nb_tokens++;
}

void	ft_strtok(t_token *tokens, char *str, char delimiter)
{
	size_t i;
	bool parenthesis;

	i = 0;
	parenthesis = false;
	tokens->nb_tokens = 0;
	tokens->tokens = malloc(sizeof(char *) * (ft_nb_tokens(str) + 1));
	if (!str || !tokens->tokens)
		return ;
	while (str[i])
	{
		if (str[i] == '(')
			parenthesis = true;
		else if (str[i] == delimiter && parenthesis == false)
			set_caca(str, i, tokens);
		else if (str[i] == ')' && parenthesis == true)
		{
			parenthesis = false;
			i++;
			set_caca(str, i, tokens);
		}
		i++;
	}
	set_caca(str, i, tokens);
	tokens->tokens[tokens->nb_tokens] = NULL;
}

bool is_shell_parameter(char *str)
{
	bool seen_egal = false;
	size_t	i;

	i = 0;
	while (str[i] == ' ')
			i++;
	while (str[i])
	{
		if (str[i] == ' ' && seen_egal == false)
		{
			printf("COMMAND NOT COMPLETE\n");
			return (false);
		}
		else if (str[i] == ' ' && seen_egal == true)
			return (true);
		else if (str[i] == '=')
		{
			seen_egal = true;
		}
		printf("Voici la lettre= %c\n", str[i]);
		i++;
	}
	if(seen_egal == true)
		return (true);
	else
		return(false);
}

char *find_param(char *command, t_parameters *node)
{
	char *tmp;
	command++;
	if (strncmp(node->name, command, ft_strlen(node->name)) == 0)
	{
		tmp = ft_strdup(node->valeur);
		return (tmp);
	}
	else
		return (NULL);
}

t_parameters	*add_parameters(char *str)
{
	t_parameters *shell_para;
	size_t		i;
	size_t		k;

	i = 0;
	shell_para = create_node_param();
	while(str[i] != '=')
		i++;
	shell_para->name = ft_substr(str, 0, i);
	shell_para->signe = str[i];
	k = i + 1;
	while(str[++i] != '\0')
		;
	shell_para->valeur = ft_substr(str, k, i - k);
	printf("NAME= '%s' | signe= '%c' | valeur= '%s'\n", shell_para->name, shell_para->signe, shell_para->valeur);
	return (shell_para);
}

t_parameters *create_node_param(void)
{
	t_parameters	*shell_para;

	shell_para = malloc(sizeof(*shell_para));
	if (!shell_para)
		return (NULL);
	shell_para->name = NULL;
	shell_para->signe = '0';
	shell_para->valeur= NULL;
	return(shell_para);
}
