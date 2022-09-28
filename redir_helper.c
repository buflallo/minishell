/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:52:02 by hlachkar          #+#    #+#             */
/*   Updated: 2022/09/22 01:59:26 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_files(int exe, int fin, int fout)
{
	if (!exe)
	{
		if (fin != 0)
			dup2(fin, 0);
		if (fout != 1)
			dup2(fout, 1);
	}
}

void	file_error(char *filename)
{
	ft_putstr_fd("minishell: no such file or directory: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putchar_fd('\n', 2);
}
