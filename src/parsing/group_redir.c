/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:09:44 by mira              #+#    #+#             */
/*   Updated: 2023/04/22 12:10:12 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

_Bool	group_redir(t_node *cmd)
{
	char	**ptr;

	while (cmd)
	{
		ptr = cmd->data->com->cmd;
		grouper(cmd, ptr);
		if (ptr && chk_redir_data(ptr))
			return (1);
		cmd = get_next_cmd_node(cmd);
	}
	return (0);
}

void	grouper(t_node *cmd, char **ptr)
{
	size_t	i;

	i = 0;
	while (i < cmd->data->com->matrix_size)
	{
		if (ptr[i] && ptr[i][0] && (ptr[i][0] == '<' || ptr[i][0] == '>'))
		{
			if (ptr[i + 1] && ptr[i + 1][0] == ' ')
			{
				ptr[i] = join_cmd(ptr[i], ptr[i + 2]);
				free(ptr[i + 1]);
				ptr[i + 1] = NULL;
				ptr[i + 2] = NULL;
			}
			else
			{
				ptr[i] = join_cmd(ptr[i], ptr[i + 1]);
				ptr[i + 1] = NULL;
			}
			update_indexes(cmd);
		}
		i++;
	}
}

_Bool	chk_redir_data(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i][0] == '>' || ptr[i][0] == '<')
		{
			if (ft_strlen(ptr[i]) < 2)
				return (rrdir(1), 1);
			else
			{
				if (ptr[i][1] == '<' || ptr[i][1] == '>')
				{
					if (!ptr[i][2])
						return (rrdir(0), 1);
				}
			}
		}
		i++;
	}
	return (0);
}

void	update_indexes(t_node *cmd)
{
	int		i;
	char	**ptr;

	while (cmd)
	{
		ptr = init_var(&i, cmd);
		while (i < (int)cmd->data->com->matrix_size)
		{
			if (!ptr[i])
			{
				swift_index(cmd, ptr);
				i = -1;
			}
			i++;
		}
		cmd = get_next_cmd_node(cmd);
	}
}

void	swift_index(t_node *cmd, char **ptr)
{
	int	j;

	j = 0;
	while (ptr[j])
		j++;
	while ((size_t)(j) < cmd->data->com->matrix_size)
	{
		ptr[j] = ptr[j + 1];
		j++;
	}
	ptr[j] = NULL;
	cmd->data->com->matrix_size -= 1;
}
