/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:14:18 by fstitou           #+#    #+#             */
/*   Updated: 2022/09/22 04:10:05 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse	*init_command(void)
{
	t_parse	*command;

	command = (t_parse *)malloc(sizeof(t_parse));
	if (!command)
		return (NULL);
	command->cmd = NULL;
	command->argv = (char **)realloc_array(NULL, strdup(""));
	command->redir = NULL;
	command->next = NULL;
	return (command);
}

t_parse	*lst_add_back_command(t_parse *lst, t_parse *new)
{
	t_parse	*tmp;

	if (!lst)
		return (new);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (lst);
}

void	parse_helper(t_token **token, t_parse *command, char *value, int type)
{
	if ((*token)->next->e_type == END || (*token)->next->e_type == PIPE
		|| (*token)->next->e_type == GREAT || (*token)->next->e_type == LESS
		|| (*token)->next->e_type == LESSANDLESS
		|| (*token)->next->e_type == GREATANDGREAT)
	{
		errors(258);
	}
	type = (*token)->e_type;
	(*token) = (*token)->next;
	value = jme3arg(token, 0);
	if (!command->redir)
		command->redir = init_redir(value, type);
	else
		command->redir = add_redir(command->redir, value, type);
}

void	parse_commands(t_token **token, t_parse *command)
{
	char	*value;
	int		type;

	value = NULL;
	type = 0;
	if ((*token)->e_type == WORD || (*token)->e_type == DQUOTE
		|| (*token)->e_type == SQUOTE || (*token)->e_type == DOLLAR)
	{
		value = jme3arg(token, 0);
		if (!command->cmd)
			command->cmd = value;
		else
			command->argv = (char **)realloc_array(command->argv, value);
	}
	else if ((*token)->e_type == GREAT || (*token)->e_type == LESS
		|| (*token)->e_type == LESSANDLESS || (*token)->e_type == GREATANDGREAT)
	{
		parse_helper(token, command, value, type);
	}
}

void	create_commands(t_token *token, t_parse **command)
{
	t_parse	*head;

	head = *command;
	while (token)
	{
		parse_commands(&token, head);
		if (token->e_type == PIPE || token->e_type == END)
		{
			if (token->next && token->e_type == PIPE
				&& token->next->e_type == END)
			{
				errors(3);
				return ;
			}
			head = add_command(head);
			head = head->next;
			token = token->next;
		}
	}
}
