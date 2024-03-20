/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:07:06 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/22 13:07:34 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

int	ft_err(char *cmd, char *msg)
{
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}

int	check_err(t_excmd *curr)
{
	t_lcmd	*cmd;

	cmd = curr->cmd;
	if (!cmd || !cmd->data)
		exit (g_status);
	if (cmd->data[0] == '.' && cmd->data[1] == '\0')
	{
		return_error(cmd->data, ": filename argument required\n", 2);
		exit(g_status);
	}
	if ((ft_strcomp(cmd->data, "./") && cmd->data[2]) || \
	(cmd->data[0] == '/' && cmd->data[1]))
	{
		return_error(cmd->data, ": No such file or directory\n", 127);
		exit (g_status);
	}
	if (!cmd->next && (cmd->data[0] == '/' || ft_strcomp(cmd->data, "./\0")))
	{
		return_error(cmd->data, ": Is a directory\n", 126);
		exit (g_status);
	}
	return_error(cmd->data, ": command not found\n", 127);
	exit (g_status);
}

int	return_error(char *cmd, char *msg, int status)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	g_status = status;
	return (1);
}

int	has_perm(char **path, char *bin, struct stat s_buf)
{
	if (s_buf.st_mode & __S_IFREG)
	{
		if (s_buf.st_mode & S_IXUSR)
			return (0);
		else
		{
			ft_putstr_fd("minishell: execve: permission denied: ", 2);
			ft_putstr_fd(bin, 2);
			ft_putchar_fd('\n', 2);
			g_status = 1;
		}
		free(bin);
		return (1);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path[1], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		g_status = 1;
	}
	return (1);
}
