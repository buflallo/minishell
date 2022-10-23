/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:17:20 by fahd              #+#    #+#             */
/*   Updated: 2022/10/10 02:29:34 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strsub(t_lexer *lexer, size_t len)
{
	unsigned int	i;
	char			*sub;

	i = 0;
	if (!lexer->str)
		return (NULL);
	sub = (char *)f_malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (i < len)
	{
		sub[i] = lexer->c;
		i++;
		advance_lexer(lexer);
	}
	sub[i] = '\0';
	return (sub);
}

t_token	*send_lexer_to_tokenize(t_lexer *lexer)
{
	t_token			*tmp;

	tmp = NULL;
	while (lexer->c)
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			advance_lexer(lexer);
		else if (lexer->c == '\'')
			tokenize_squote(&tmp, lexer);
		else if (lexer->c == 34)
			tokenize_dquote(&tmp, lexer);
		else if (lexer->c == '|')
			tokenize_pipe(&tmp, lexer);
		else if (lexer->c == '<')
			tokenize_in_redir(&tmp, lexer);
		else if (lexer->c == '>')
			tokenize_out_redir(&tmp, lexer);
		else if (lexer->c == '$')
			tokenize_dollar(&tmp, lexer);
		else
			tokenize_word(&tmp, lexer);
	}
	tokenize_end(&tmp);
	return (tmp);
}

void	dollar(t_lexer *lexer, t_token **tmp, t_token **token)
{
	int		type;
	char	*val;

	type = DOLLAR;
	val = ft_strsub(lexer, 1);
	if (lexer->c == '\0')
		val = ft_strjoin(val, " ", 0);
	if (lexer->c == '0' || !ft_isdigit(lexer->c))
	{
		if (lexer->c == '$')
			val = ft_strjoin(val, ft_strsub(lexer, 1), 2);
		else if (lexer->c == ' ')
			val = ft_strjoin(val, " ", 0);
		else if (lexer->c == '?')
		{
			val = ft_strjoin(val, ft_strsub(lexer, 1), 2);
		}
		(*token) = init_token(val, type);
		if (lexer->c != '\0')
			(*token)->flag = 1;
		(*tmp) = lst_add_back((*tmp), (*token));
	}
	else
		advance_lexer(lexer);
}

void	word(t_lexer *lexer, t_token **token, t_token **tmp)
{
	int		size;
	int		type;
	char	*val;

	size = 0;
	type = WORD;
	if (token_index(&(lexer->str[lexer->i])))
		size = token_index(&(lexer->str[lexer->i]));
	else if (ft_int_strchr(&(lexer->str[lexer->i]), '$') > 0)
		size = ft_int_strchr(&(lexer->str[lexer->i]), '$');
	else
		size = ft_int_strchr(&(lexer->str[lexer->i]), '\0');
	val = ft_strsub(lexer, size);
	(*token) = init_token(val, type);
	(*token)->flag = 1;
	(*tmp) = lst_add_back((*tmp), (*token));
}

char	*expand_dollar(char *dq_content, int exec)
{
	t_token	*token;
	t_token	*tmp;
	t_lexer	*lexer;
	char	*result;

	tmp = NULL;
	token = NULL;
	result = ft_strdup("");
	lexer = ft_init_lexer(dq_content, dq_content[0]);
	while (lexer->c)
	{
		if (lexer->c == '$')
			dollar(lexer, &tmp, &token);
		else
			word(lexer, &token, &tmp);
	}
	token = init_token("", END);
	token->flag = 0;
	tmp = lst_add_back(tmp, token);
	result = jme3arg(&tmp, exec, 2);
	return (result);
}
