/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:11:14 by fstitou           #+#    #+#             */
/*   Updated: 2022/10/19 16:37:54 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*normal_or_qu(t_token **b, int exec, char *str)
{
	if (!(*b)->val[1])
		return (normal_expansion(b, 1));
	else
		return (dollar_qu(b, exec, str));
}

char	*dollar_qu(t_token **b, int exec, char *str)
{
	(void)exec;
	if ((*b)->val[1] == '?')
		str = ft_strjoin(str, ft_itoa(g_vars.exit_status), 2);
	else if ((*b)->val[1] == ' ')
		str = ft_strjoin(str, ft_strdup("$"), 2);
	else if ((*b)->val[1] == '$')
		str = ft_strjoin(str, ft_strdup("$$"), 2);
	(*b) = (*b)->next;
	return (str);
}

char	*check_end(t_token **b, char *str, int exec)
{
	if ((*b) && (*b)->e_type == DQUOTE)
	{
		str = ft_strjoin(str, expand_dollar((*b)->val, exec), 2);
		(*b) = (*b)->next;
	}
	else if ((*b) && (*b)->e_type != END)
	{
		str = ft_strjoin(str, (*b)->val, 0);
		(*b) = (*b)->next;
	}
	return (str);
}

char	*jme3arg(t_token **b, int exec, int ch_d)
{
	char	*str;

	str = ft_strdup("");
	// print_tokens(*b);
	// exit(0);
	while ((*b) && (*b)->flag == 1)
	{
		if ((*b)->e_type == DOLLAR && exec)
			checkin_dollar(b, &str, ch_d);
		if ((*b)->e_type == DQUOTE)
			str = ft_strjoin(str, expand_dollar((*b)->val, exec), 2);
		else if ((*b)->e_type != END && ((*b)->e_type != DOLLAR || !exec))
			str = ft_strjoin(str, (*b)->val, 0);
		if ((*b)->flag == 1)
			(*b) = (*b)->next;
		else
		{
			(*b) = (*b)->next;
			return (str);
		}
	}
	if ((*b) && (*b)->e_type == DOLLAR && exec)
		return (normal_or_qu(b, exec, str));
	str = check_end(b, str, exec);
	return (str);
}
