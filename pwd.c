/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 02:33:17 by hlachkar          #+#    #+#             */
/*   Updated: 2022/09/22 01:48:14 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_putstr_fd("pwd: cannot get current working directory\n", 2);
		g_vars.exit_status = 1;
		return (g_vars.exit_status);
	}
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	g_vars.exit_status = 0;
	return (g_vars.exit_status);
}
