/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:19:46 by avassor           #+#    #+#             */
/*   Updated: 2023/04/22 13:14:42 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

static int	exe(t_exec *exec, t_excmd *curr, int fd[2], int i)
{
	if (curr->cmd && ft_strcomp(curr->cmd->data, "./minishell\0"))
		run_signals(5);
	else
		run_signals(2);
	if (!check_builtin(curr))
	{
		if (exec_buil_pipe(exec, curr, fd, i))
			return (1);
		return (0);
	}
	else if (!ft_run(exec, curr, fd))
	{
		return (0);
	}
	return (1);
}

static int	retrieve_exec(t_excmd *curr, t_exec *exec, int fd[2], int i)
{
	if (exec->pipes == 0)
		std_fd(fd);
	else
		get_fd(exec, fd, i);
	exe(exec, curr, fd, i);
	return (0);
}

static void	zombie_process(void)
{
	while (waitpid(-1, &g_status, 0) > 0)
		;
	if (WTERMSIG(g_status) == 2 || g_status == 130)
		g_status = 130;
	else if (WTERMSIG(g_status) == 3)
		g_status = 131;
	else if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
	if (g_status == 13)
		g_status = 0;
}

int	execute(t_trunk *tree, t_env *envp, char **arrenv)
{
	t_node	*cmd;
	t_exec	*exec;
	int		fd[2];
	int		i;

	i = 0;
	exec = exec_init(tree, envp, arrenv);
	cmd = tree->leafs;
	if (!exec)
		return (1);
	if (pied_piper(exec, i))
		return (1);
	if ((tree->an->here_doc && mng_here_doc(exec, cmd)))
		return (free_exec(exec), 0);
	while (cmd)
	{
		if (cmd->data->com && cmd->data->com->excmd)
			if (retrieve_exec(cmd->data->com->excmd, exec, fd, i))
				return (EXIT_FAILURE);
		cmd = get_next_cmd_node(cmd);
		i++;
	}
	exec_end(exec, tree, envp);
	zombie_process();
	return (free_exec(exec), 0);
}

int	ft_run(t_exec *exec, t_excmd *curr, int *fd)
{
	char	*run;
	char	**args;

	run = NULL;
	args = NULL;
	exec->pid = fork();
	g_status = 0;
	if (exec->pid < 0)
		return (-1);
	sig_child();
	if (!exec->pid)
	{
		if (is_redir(curr, fd))
			return (1);
		fd_init(exec, fd);
		if (curr->cmd)
			child_process(exec, curr, run, args);
	}
	return (0);
}
