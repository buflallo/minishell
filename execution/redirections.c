/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:45:13 by fahd              #+#    #+#             */
/*   Updated: 2022/10/19 18:51:57 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_pipes(t_parse *cmd, int in, int i, int *fd)
{
	if (cmd->next->cmd != NULL || cmd->next->redir != NULL)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}
	if (i != 0) // the second command dup the input from last pipe read end
	{
		dup2(in, 0);
		close(fd[1]);
		close(fd[0]);
	}
}

void	pipe_redir(t_parse *cmd, int in, int index, int *fd)
{
	dup_pipes(cmd, in, index, fd); // dup the pipes
	open_redir(cmd, 0); // open the redirections and override the pipes
}

int	append_trunc(t_redir *redir)
{
	int	fout;

	fout = 1;
	if (redir->file[0] == 'z' || redir->file[0] == '\0')
	{
		if (redir->file[0] == '\0')
		{
			g_vars.g_err = 1;
			file_error(redir->file);
		}
		else if (redir->file[0] == 'z')
			errors(6);
		return (1);
	}
	else if (redir->e_type == GREAT)
	{
		redir->fdout = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		fout = redir->fdout;
	}
	else
	{
		redir->fdout = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		fout = redir->fdout;
	}
	return (fout);
}

int	open_read(t_redir *redir, t_parse *cmd, int exec)
{
	int	fin;

	fin = 0;
	if (redir->e_type == LESS)
	{	
		if (access(redir->file, F_OK) == -1)
		{
			file_error(redir->file);
			g_vars.exit_status = 1;
			if (exec)
				return (-1);
			exit(g_vars.exit_status);
		}
		else
		{
			redir->fdin = open(redir->file, O_RDONLY);
			fin = redir->fdin;
		}
	}
	else
	{
		if (cmd->cmd)
			dup2(redir->fdin, 0);
	}
	return (fin);
}

void	open_redir(t_parse *head, int exe)
{
	t_redir	*tmp;
	int		fout;
	int		fin;

	fin = 0;
	fout = 1;
	tmp = head->redir;
	while (tmp != NULL)
	{
		if (tmp->e_type == GREAT || tmp->e_type == GREATANDGREAT)
		{
			fout = append_trunc(tmp);
			if (fout == 1)
				break;
			
		}
		else if (tmp->e_type == LESS || tmp->e_type == LESSANDLESS)
		{
			fin = open_read(tmp, head, exe);
			if (fin == -1)
				break ;
		}
		tmp = tmp->next;
	}
	dup_files(exe, fin, fout);
}
