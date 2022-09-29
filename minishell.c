/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:45:32 by hlachkar          #+#    #+#             */
/*   Updated: 2022/09/24 05:21:31 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(void)
{
	printf("exit\n");
	exit(g_vars.exit_status);
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

t_token	*parse_cmd(t_token *tokens)
{
	t_lexer	*lexer;

	lexer = ft_init_lexer(g_vars.line, g_vars.line[0]);
	tokens = send_lexer_to_tokenize(lexer);
	free(lexer);
	return (tokens);
}

void	init_gs_and_c_signal(void)
{
	g_vars.exit_sig = 0;
	g_vars.g_err = 0;
	c_signal();
}

int	main(int ac, char *av[], char **env)
{
	t_parse	*commands;
	t_token	*tokens;
	
	(void)ac;
	(void)av;
	init_env(env);
	while (1)
	{
		init_gs_and_c_signal();
		g_vars.line = readline("MISSI-1.0$ ");
		if (!g_vars.line)
			exit_shell();
		if (only_enter())
			continue ;
		commands = init_command();
		tokens = parse_cmd(tokens);
		create_commands(tokens, &commands);
		add_history(g_vars.line);
		if (!g_vars.g_err)
		{
			// read_heredocs(commands);
			if (g_vars.exit_sig != -27)
			{
				exec_pipeline(commands, &g_vars.my_env);
			}
		}
	}
}
