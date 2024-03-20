/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 22:42:48 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/22 11:42:13 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

void	free_here_doc(t_exec *exec, t_node *node)
{
	t_excmd	*curr;

	curr = node->data->com->excmd;
	if (exec)
		free_exec(exec);
	free(curr->in);
	curr->in = NULL;
}

void	exec_end(t_exec *exec, t_trunk *tree, t_env *envp)
{
	if (exec->envp != envp)
		tree->envp = exec->envp;
	close_fds(exec);
}

_Bool	mng_here_doc(t_exec *exec, t_node *cmd)
{
	t_excmd	*curr;

	curr = NULL;
	while (cmd)
	{
		if (cmd->data->com && cmd->data->com->excmd)
			curr = cmd->data->com->excmd;
		if (curr && curr->heredoc)
			if (go_and_read(exec, curr))
				return (1);
		cmd = get_next_cmd_node(cmd);
	}
	return (0);
}

int	hd_quit(int dupl, char *stream, char *c, t_exec *exec)
{
	if (g_status == 130)
	{
		dup2(dupl, STDIN_FILENO);
		free(stream);
		free(c);
		exec->hd_err = 1;
		return (1);
	}
	if (!stream || (!stream && g_status == 131))
	{
		if (g_status == 131)
			exec->hd_err = 1;
		free(stream);
		return (1);
	}
	return (0);
}
