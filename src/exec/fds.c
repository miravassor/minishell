/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:04:27 by mira              #+#    #+#             */
/*   Updated: 2023/04/21 22:27:09 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

void	close_fds(t_exec *exec)
{
	int	i;

	i = 0;
	if (exec->pipes)
	{
		while (i < (exec->pipes * 2))
		{
			close(exec->fd[i]);
			i++;
		}
	}
}

int	pied_piper(t_exec *exec, int i)
{
	while (i < exec->pipes)
	{
		if (pipe(exec->fd + (i * 2)) < 0)
		{
			printf("minishell: error opening pipe\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	get_fd(t_exec *exec, int fd[2], int i)
{
	if (i == 0)
	{
		fd[0] = STDIN_FILENO;
		fd[1] = exec->fd[1];
	}
	else if (i > 0)
	{
		fd[0] = exec->fd[(i - 1) * 2];
		if (i == exec->pipes)
			fd[1] = STDOUT_FILENO;
		else
			fd[1] = exec->fd[i * 2 + 1];
	}
}

void	std_fd(int fd[2])
{
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
}

void	fd_init(t_exec *exec, int fd[2])
{
	(void)exec;
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
	close_fds(exec);
}
