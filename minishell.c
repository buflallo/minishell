/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:45:32 by fahd              #+#    #+#             */
/*   Updated: 2022/10/19 16:41:45 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(void)
{
	printf("exit\n");
	exit(g_vars.exit_status);
}

t_token	*create_tokens(t_token *tokens)
{
	t_lexer	*lexer;

	lexer = NULL;
	lexer = ft_init_lexer(g_vars.line, g_vars.line[0]);
	tokens = send_lexer_to_tokenize(lexer);
	return (tokens);
}

void	init_gs_and_c_signal(void)
{
	g_vars.line = NULL;
	g_vars.exit_sig = 0;
	g_vars.g_err = 0;
	c_signal();
}

void	mino(t_parse *cmds)
{
	if (!g_vars.g_err)
	{
		read_heredocs(cmds);
		if (g_vars.exit_sig != -27) // -27 is the exit code for ctrl + C
			exec_pipeline(cmds, &g_vars.my_env);
	}
}

void print_commands(t_parse *commands)
{
	int i;
	while(commands)
	{
		i = 0;
		printf("%s ", commands->cmd);
		while(commands->argv[i])
		{
			printf("%s ", commands->argv[i]);
			i++;
		}
		while (commands->redir)
		{
			if (commands->redir->e_type == 5)
				printf(">>");
			else if (commands->redir->e_type == 6)
				printf("<<");
			else if (commands->redir->e_type == 7)
				printf(">");
			else if (commands->redir->e_type == 8)
				printf("<");
			printf("%s ", commands->redir->file);
			commands->redir = commands->redir->next;
		}
		if (commands->next)
			printf("| ");
		else
			printf("\n");
		commands = commands->next;
	}
}

void print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("%s ", tokens->val);
		tokens = tokens->next;
	}
	printf("\n");
}

int	main(int ac, char *av[], char **env)
{
	t_parse	*commands;
	t_token	*tokens;

	commands = NULL;
	tokens = NULL;
	(void)ac;
	(void)av;
	g_vars.index = 0;
	init_env(env);
	while (1)
	{
		init_gs_and_c_signal();
		g_vars.line = readline("missi-1.0$ ");
		if (!g_vars.line)
			exit_shell();
		if (only_enter())
			continue ;
		commands = init_command();
		tokens = create_tokens(tokens);
		// print_tokens(tokens);
		create_commands(tokens, &commands);
		add_history(g_vars.line);
		mino(commands);
		free(g_vars.line);
	}
}
