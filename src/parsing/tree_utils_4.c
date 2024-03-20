/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:49:56 by mira              #+#    #+#             */
/*   Updated: 2023/04/19 17:46:11 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

_Bool	check_tkn_type(t_node_cmd *cmd, t_tkn *tkn)
{
	if (tkn->id == CHAR || tkn->id == CSPACE)
		return (1);
	else if (chk_morrrr(cmd, tkn))
		return (1);
	else
		if (cmd->state && tkn->id != END && tkn->id != PIPE)
			return (1);
	return (0);
}

_Bool	chk_morrrr(t_node_cmd *cmd, t_tkn *tkn)
{
	if (tkn->id == SMPLQUOT || tkn->id == DBLQUOT)
	{
		cmd->quotes = 1;
		if (!cmd->state)
			cmd->state = 1;
		else
			cmd->state = 0;
		return (1);
	}
	else if (tkn->id == DOT || tkn->id == SLASH)
	{
		cmd->path = 1;
		return (1);
	}
	else if (tkn->id == ENV)
	{
		cmd->env = 1;
		return (1);
	}
	else if (tkn->id == GREATR || tkn->id == LESS)
		return (1);
	return (0);
}

t_tkn	*tkn_err(void)
{
	t_tkn	*new;

	new = (t_tkn *)malloc(sizeof(t_tkn));
	if (!new)
		return (NULL);
	new->data = NULL;
	new->err = 1;
	new->id = -1;
	new->next = NULL;
	new->prev = NULL;
	new->size = 0;
	return (new);
}

void	pipe_placer(t_trunk *trunk, t_node *node)
{
	node = trunk->leafs;
	while (node->type == N_PIPE)
		node = node->data->pip->in;
	trunk->leafs = node;
}

int	clearrr(t_node *cmd, char **ptr, int i)
{
	while (!ptr[i] && i < (int)cmd->data->com->matrix_size)
		i++;
	if (i < (int)cmd->data->com->matrix_size
		&& ptr[i] && ptr[i][0] == ' ' && !ptr[i][1])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i = -1;
	}
	return (i);
}
