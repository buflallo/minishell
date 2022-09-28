/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 03:00:20 by hlachkar          #+#    #+#             */
/*   Updated: 2022/09/24 06:30:05 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_child(int sig)
{
	if (sig == SIGINT)
	{
		if (g_vars.exit_sig == 27)
		{
			g_vars.exit_sig = -27;
			ft_putchar_fd('\n', 0);
			close(rl_instream->_fileno);
			// close(rl_instream->_file);
		}
		else
		{
			ft_putchar_fd('\n', 0);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_vars.exit_status = 1;
	}
	else if (sig == SIGQUIT)
	{
		ft_putchar_fd('\r', STDERR_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler(int sig)
{
	if (!kill(g_vars.pid, sig))
	{
		if (sig == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			g_vars.exit_status = 131;
		}
		else if (sig == SIGINT)
		{
			ft_putstr_fd("\n", 1);
			g_vars.exit_status = 130;
		}
	}
	else
		sig_child(sig);
}

void	ctl_plus(int sig)
{
	if (g_vars.pid != 0)
		sig_handler(sig);
	else
		sig_child(sig);
}

void	c_signal(void)
{
	signal(SIGINT, ctl_plus);
	signal(SIGQUIT, ctl_plus);
}
