/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:19:46 by avassor           #+#    #+#             */
/*   Updated: 2023/04/21 23:14:46 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

void	fd_error(t_excmd *curr, int fd)
{
	if (fd == -42)
		return_error(NULL, "syntax error near unexpected token `newline'\n", 2);
	else if (curr->in)
		return_error(curr->in->data + 1, ": No such file or directory\n", 2);
	else if (curr->out)
		return_error(curr->out->data + 1, ": No such file or directory\n", 2);
	exit (g_status);
}

_Bool	file_opener(t_excmd *curr, int fd[2])
{
	if (curr->heredoc || curr->in)
	{
		if (fd[0] != 0)
			close(fd[0]);
		fd[0] = create_file_in(curr);
		if (fd[0] == 0)
			return (1);
	}
	if (curr->appen || curr->out)
	{
		if (fd[1] != 1)
			close(fd[1]);
		fd[1] = create_file_out(curr);
		if (fd[1] == 1)
			return (1);
	}
	if (fd[0] < 0 || fd[1] < 0)
		return (1);
	if (!curr->cmd)
	{
		close(fd[0]);
		close(fd[1]);
	}
	return (0);
}

int	create_file_in(t_excmd *curr)
{
	t_lcmd	*ptr;
	int		fd;

	ptr = curr->in;
	fd = 0;
	close_fd(fd, 0);
	while (ptr)
	{
		if (ptr->data[0] == '<')
			fd = open(&ptr->data[1], O_RDONLY);
		else
			return (-1);
		if (fd < 0)
			return (fd_error(curr, fd), 1);
		ptr = ptr->next;
	}
	return (fd);
}

int	create_file_out(t_excmd *curr)
{
	t_lcmd	*ptr;
	int		fd;

	ptr = curr->out;
	fd = 1;
	close_fd(fd, 1);
	while (ptr)
	{
		if (ptr->data[0] == '>' && ptr->data[1] && ptr->data[1] == '>')
			fd = open(&ptr->data[2], O_CREAT | O_RDWR | O_APPEND, 0644);
		else if (ptr->data[0] == '>')
			fd = open(&ptr->data[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		else
			return (-1);
		if (fd < 0)
			return (fd_error(curr, fd), 1);
		ptr = ptr->next;
	}
	return (fd);
}
