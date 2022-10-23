/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 22:35:52 by fstitou           #+#    #+#             */
/*   Updated: 2022/10/10 02:29:34 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*ft_init_lexer(char *str, char c)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)f_malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->str = str;
	lexer->c = c;
	lexer->i = 0;
	return (lexer);
}

t_lexer	*advance_lexer(t_lexer *lexer)
{
	lexer->i++;
	lexer->c = lexer->str[lexer->i];
	return (lexer);
}

void	tokenize_in_redir(t_token **tmp, t_lexer *lexer)
{
	t_token	*token;
	int		type;
	char	*val;

	token = NULL;
	if (lexer->str[lexer->i + 1] == '<')
	{
		type = LESSANDLESS;
		val = ft_strsub(lexer, 2);
		token = init_token(val, type);
		*tmp = lst_add_back(*tmp, token);
	}
	else
	{
		type = LESS;
		val = ft_strsub(lexer, 1);
		token = init_token(val, type);
		*tmp = lst_add_back(*tmp, token);
	}
}

void	tokenize_pipe(t_token **tmp, t_lexer *lexer)
{
	t_token	*token;
	int		type;
	char	*val;

	token = NULL;
	type = PIPE;
	val = ft_strsub(lexer, 1);
	token = init_token(val, type);
	*tmp = lst_add_back(*tmp, token);
}

void	tokenize_end(t_token **tmp)
{
	t_token	*token;

	token = NULL;
	token = init_token("", END);
	*tmp = lst_add_back(*tmp, token);
}
