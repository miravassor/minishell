/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:26:18 by mira              #+#    #+#             */
/*   Updated: 2023/04/21 20:44:15 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

size_t	check_red(t_node *cmd)
{
	size_t	i;

	i = 0;
	while (cmd)
	{
		i = 0;
		while (cmd->data->com->cmd && cmd->data->com->cmd[i])
		{
			if (*cmd->data->com->cmd[i] == '<'
				|| *cmd->data->com->cmd[i] == '>')
				if (illegal_line(cmd->data->com->cmd[i])
					|| illegal_redir(cmd->data->com->cmd[i + 1]))
					return (1);
			i++;
		}
		cmd = get_next_cmd_node(cmd);
	}
	return (0);
}

size_t	chk_unclosed_quotes(char *line)
{
	char	quote;

	quote = *line;
	line++;
	if (quote == '\'' || quote == '\"')
	{
		while (*line)
		{
			if (*line == quote)
				return (0);
			line++;
		}
		return (1);
	}
	return (0);
}

size_t	check_quotes(t_node *cmd)
{
	size_t	i;
	char	*ptr;

	while (cmd)
	{
		i = 0;
		if (cmd->data->com->quotes)
		{
			if (cmd->data->com->cmd)
			{
				ptr = cmd->data->com->cmd[i];
				while (ptr)
				{
					if (chk_unclosed_quotes(ptr))
						return (g_status = 2, 1);
					i++;
					ptr = cmd->data->com->cmd[i];
				}
			}
		}
		cmd = get_next_cmd_node(cmd);
	}
	return (0);
}

_Bool	syntaxr(t_node *node, t_env *envp)
{
	clear_empty_quotes(node);
	if (check_red(node))
		return (rror(SYNTAX), 1);
	if (check_quotes(node))
		return (1);
	if (expandr(node, envp) || clear_empty_quotes(node))
		return (1);
	clear_spaces(node);
	clear_null(node);
	if (group_redir(node))
		return (1);
	clear_null(node);
	group_cmd(node);
	clear_null(node);
	return (0);
}
