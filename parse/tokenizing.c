/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:26:06 by fahd              #+#    #+#             */
/*   Updated: 2022/10/10 02:29:34 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*init_token(char *val, int type)
{
	t_token	*token;

	token = (t_token *)f_malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->val = val;
	token->next = NULL;
	token->e_type = type;
	token->flag = 0;
	return (token);
}

t_token	*lst_add_back(t_token *lst, t_token *new)
{
	t_token	*tmp;

	if (!lst)
		return (new);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (lst);
}

int	ft_is_space(void)
{
	int	i;

	i = 0;
	while (g_vars.line[i])
	{
		if (g_vars.line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	*f_malloc(size_t size)
{
	void	*tmp;

	tmp = malloc(size);
	if (!tmp)
		return (NULL);
	g_vars.alloc[g_vars.index] = tmp;
	g_vars.index++;
	return (tmp);
}

char	*if_only_dollar(t_lexer *lexer)
{
	char	*val;

	val = ft_strsub(lexer, 1);
	if (lexer->c == '\0')
	{
		val = ft_strjoin(val, " ", 0);
		return (val);
	}
	return (val);
}
