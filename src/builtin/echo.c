/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:34:00 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/21 23:15:42 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

static int	echo_check_n(t_lcmd *cmd)
{
	size_t	i;
	int		check;

	check = 0;
	while (cmd)
	{
		i = 1;
		if (cmd->data[0] == '-' && cmd->data[i] == 'n')
		{
			while (cmd->data[i] == 'n' && cmd->data[i + 1] != '\0')
				i++;
			if (cmd->data[i] == 'n' || (cmd->data[i] == 'n' && \
				cmd->next->data[0] == ' '))
					check += 1;
			else
				return (check);
		}
		if (cmd->next && !ft_strcomp(cmd->next->data, "-n"))
			return (check);
		cmd = cmd->next;
	}
	return (check);
}

static int	ft_echo(t_lcmd *cmd)
{
	while (cmd)
	{
		ft_putstr_fd(cmd->data, 1);
		if (cmd->next && cmd->next->data[0] == '\0')
		{
			while (*cmd->next->data == '\0')
			{
				if (!cmd->next->next)
					break ;
				cmd = cmd->next;
			}
		}
		if (cmd->next)
			write(1, " ", 1);
		else
			break ;
		cmd = cmd->next;
	}
	return (0);
}

static int	print_echo_2(t_lcmd *cmd)
{
	if (echo_check_n(cmd))
	{
		while (echo_check_n(cmd) > 0)
		{
			if (cmd->next && (cmd->next->data[0] != '-' && \
				cmd->next->data[1] != 'n'))
			{
				cmd = cmd->next;
				break ;
			}
			cmd = cmd->next;
		}
		ft_echo(cmd);
		return (0);
	}
	else
	{
		cmd = cmd->next;
		ft_echo(cmd);
		printf("\n");
		return (0);
	}
	return (1);
}

int	print_echo_1(t_excmd *curr)
{
	t_lcmd	*cmd;

	cmd = curr->cmd;
	if (cmd && cmd->next && cmd->next->data[0] == '$' && \
		cmd->next->data[1] == '?')
	{
		printf("%d\n", g_status);
		return (0);
	}
	g_status = 0;
	if (cmd)
	{
		print_echo_2(cmd);
		return (0);
	}
	return (1);
}
