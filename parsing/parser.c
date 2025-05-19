#include "../includes/parsing.h"

static t_cmd *init_new_cmd(void)
{
	t_cmd *new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->redir = NULL;
	new->next = NULL;
	return new;
}

static void	add_cmd(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!*cmd_list)
		*cmd_list = new_cmd;
	else
	{
		tmp = *cmd_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
	}
}

int parse_tokens(t_token *tokens, t_shell *shell)
{
	t_token *current = tokens;
	t_cmd *current_cmd = NULL;
	char **args = NULL;
	int arg_count = 0;

	while (current)
	{
		if (current->value[0] == '|')
		{
			if (!current_cmd)
				return syntax_error("Unexpected pipe");
			if (arg_count > 0 || current_cmd->redir)
			{
				args = realloc(args, (arg_count + 1) * sizeof(char *));
				args[arg_count] = NULL;
				current_cmd->cmd = args;
				args = NULL;
				arg_count = 0;
			}
			add_cmd(&shell->cmd, current_cmd);
			current_cmd = NULL;
			shell->nb_pipe++;
			current = current->next;
		}
		else if (is_redirection(current))
		{
			if (!current_cmd)
				current_cmd = init_new_cmd();
			if (!handle_redirection(&current, &current_cmd->redir))
				return (0);
		}
		else
		{
			if (!current_cmd)
				current_cmd = init_new_cmd();
			args = realloc(args, (arg_count + 1) * sizeof(char *));
			args[arg_count++] = ft_strdup(current->value);
			current = current->next;
		}
	}
	if (current_cmd)
	{
		args = realloc(args, (arg_count + 1) * sizeof(char *));
		args[arg_count] = NULL;
		current_cmd->cmd = args;
		add_cmd(&shell->cmd, current_cmd);
	}
	return (1);
}
