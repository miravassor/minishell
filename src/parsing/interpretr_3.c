/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretr_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:14:42 by mira              #+#    #+#             */
/*   Updated: 2023/04/21 13:20:57 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

_Bool	build_link(t_node *node, char **cmd)
{
	t_excmd	*head;

	head = init_excmd();
	if (!head)
		return (1);
	head->in = extract_data(head, cmd, '<', node->data->com->matrix_size);
	if (head->enomem)
		return (1);
	head->out = extract_data(head, cmd, '>', node->data->com->matrix_size);
	if (head->enomem)
		return (1);
	head->cmd = init_lcmd(NULL, NULL);
	if (!head->cmd)
		return (1);
	return (end_link(node, head, cmd));
}

_Bool	end_link(t_node *node, t_excmd *head, char **cmd)
{
	int		wrk;

	wrk = 0;
	if (chkcmd(node, cmd))
		wrk = extract_cmd(node, head, cmd);
	if (wrk < 0)
		return (1);
	if (!wrk)
	{
		free(head->cmd);
		head->cmd = NULL;
	}
	node->data->com->excmd = head;
	return (0);
}

_Bool	chkcmd(t_node *node, char **cmd)
{
	size_t	i;

	i = 0;
	while (i < node->data->com->matrix_size)
	{
		if (cmd[i])
			return (1);
		i++;
	}
	return (0);
}

int	extract_cmd(t_node *node, t_excmd *head, char **cmd)
{
	size_t	size;
	size_t	i;
	int		wrk;

	init_extract(&size, &i, &wrk);
	while (cmd && !cmd[i])
		i++;
	while (size <= node->data->com->matrix_size)
	{
		if (cmd[size])
		{
			if (cmd[size][0] && cmd[size][0] == ' ')
				free_dim(cmd, size);
			else
			{
				if (swap_index(head->cmd, cmd[size]))
					return (-1);
				cmd[size] = NULL;
			}
			wrk += 1;
		}
		size++;
	}
	return (wrk);
}

_Bool	free_dim(char **cmd, size_t size)
{
	free(cmd[size]);
	cmd[size] = NULL;
	return (1);
}
