/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 22:59:24 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/21 22:59:25 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

int	check_exit(t_excmd *curr)
{
	t_lcmd	*cmd;

	cmd = curr->cmd;
	if (cmd->next && !is_numeric(cmd->next->data) && count_cmd(curr) >= 2)
	{
		g_status = 2;
		return_error(cmd->next->data, ": error numeric required\n", 2);
		exit (g_status);
	}
	else if (cmd->next && is_numeric(cmd->next->data) && count_cmd(curr) > 2)
	{
		g_status = 1;
		return (return_error("exit", ": too many arguments\n", 1), 1);
	}
	else if (cmd->next && is_numeric(cmd->next->data) && count_cmd(curr) == 2)
	{
		g_status = ft_atoi(cmd->next->data) % 256;
		exit (g_status);
	}
	return (0);
}

int	display_status(t_exec *exec, t_excmd *curr)
{
	t_lcmd	*cmd;

	cmd = curr->cmd;
	if (count_cmd(curr) == 1)
	{
		printf("%s\n", cmd->data);
		close(exec->in);
		close(exec->out);
		exit(g_status);
	}
	if (cmd)
	{
		close(exec->in);
		close(exec->out);
		check_exit(curr);
		return (0);
	}
	else
	{
		if (exec)
			free_exec(exec);
		exit(g_status);
	}
	return (0);
}
