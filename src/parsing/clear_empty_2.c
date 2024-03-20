/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_empty_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:13:43 by mira              #+#    #+#             */
/*   Updated: 2023/04/18 15:02:07 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

_Bool	clear_empty_quotes(t_node *cmd)
{
	char	**ptr;

	while (cmd)
	{
		if (cmd->data->com->quotes)
		{
			ptr = cmd->data->com->cmd;
			clear_me(cmd, ptr);
		}
		cmd = get_next_cmd_node(cmd);
	}
	return (0);
}

void	clear_me(t_node *cmd, char **ptr)
{
	int	i;

	i = 0;
	while (i < (int)cmd->data->com->matrix_size)
	{
		if (ptr[i] && (ptr[i][0] == '\"' || ptr[i][0] == '\''))
		{
			if (ptr[i][1] && (ptr[i][1] == '\"' || ptr[i][1] == '\''))
			{
				free(ptr[i]);
				ptr[i] = NULL;
				i = shift_index(cmd, ptr);
			}
		}
		i++;
	}
}

int	shift_index(t_node *cmd, char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
		i++;
	if (!i)
	{
		free(ptr);
		cmd->data->com->cmd = NULL;
		cmd->data->com->matrix_size = 0;
		return (-1);
	}
	while (ptr[i + 1])
	{
		ptr[i] = ptr[i + 1];
		i++;
	}
	ptr[i] = NULL;
	cmd->data->com->matrix_size -= 1;
	return (-1);
}
