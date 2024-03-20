/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:30:05 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/21 22:57:00 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

int	exec_buil_pipe(t_exec *exec, t_excmd *curr, int fd[2], int i)
{
	int	ret;

	ret = ft_run_built_2(exec, curr, fd, i);
	return (ret);
}

int	fds_built(int fd[2], t_excmd *curr, t_exec *exec)
{
	exec->in = dup(STDIN_FILENO);
	exec->out = dup(STDOUT_FILENO);
	if (is_redir(curr, fd))
	{
		close(exec->out);
		close(exec->in);
		return (1);
	}
	if (fd[0] != 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (fd[1] != 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	return (0);
}

void	dup_built(t_exec *exec)
{
	dup2(exec->in, STDIN_FILENO);
	dup2(exec->out, STDOUT_FILENO);
	if (exec->in != 0)
		close(exec->in);
	if (exec->out != 1)
		close(exec->out);
}

static _Bool	ft_run_built_1(t_exec *exec, t_excmd *curr)
{
	int	ret;

	ret = 0;
	if (!ft_strncmp(curr->cmd->data, "echo\0", 5))
		ret = print_echo_1(curr);
	else if (!ft_strncmp(curr->cmd->data, "cd", 2))
		ret = ft_cd_1(curr, exec);
	else if (!ft_strncmp(curr->cmd->data, "env\0", 4))
	{
		if (curr->cmd->next)
			ret = 0;
		else
			ret = print_env(exec);
	}
	else if (!ft_strncmp(curr->cmd->data, "pwd\0", 4))
		ret = ft_pwd();
	else if (!ft_strncmp(curr->cmd->data, "exit", 4))
		ret = display_status(exec, curr);
	return (ret);
}

_Bool	ft_run_built_2(t_exec *exec, t_excmd *curr, int fd[2], int i)
{
	int	ret;

	ret = 0;
	if (fds_built(fd, curr, exec))
		return (1);
	ret = ft_run_built_1(exec, curr);
	if (!exec->pipes || i == 0 || i == exec->pipes)
	{
		if (!ft_strncmp(curr->cmd->data, "unset\0", 6))
			ret = ft_unset(exec, curr);
		else if (!ft_strncmp(curr->cmd->data, "export\0", 7))
			ret = ft_export(exec, curr);
		else if (!ft_strncmp(curr->cmd->data, "$?\0", 3))
			ret = return_code();
	}
	else
		ret = 0;
	dup_built(exec);
	return (ret);
}
