/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanr_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:54:30 by avassor           #+#    #+#             */
/*   Updated: 2023/04/21 22:51:01 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

void	free_tkn(t_tkn *tkn)
{
	t_tkn	*tmp;

	while (tkn)
	{
		tmp = tkn->next;
		if (tkn->data)
			free(tkn->data);
		free(tkn);
		tkn = tmp;
	}
}

void	free_trunk_root(t_trunk *tree)
{
	if (tree->an)
		free(tree->an);
}

void	free_matrix(char **cmd, size_t matrix)
{
	char		**ptr;
	size_t		i;

	ptr = NULL;
	ptr = cmd;
	i = 0;
	while (i < matrix)
	{
		if (cmd[i])
			free(cmd[i]);
		i++;
	}
	free(ptr);
}

t_node	*free_cmd(t_node *node)
{
	t_node	*tmp;

	tmp = NULL;
	if (node->data->com->pipe_parent)
		tmp = node->data->com->pipe_parent;
	if (node->data->com)
	{
		if (node->data->com->excmd)
			free_list(node->data->com->excmd);
	}
	if (node->data->com->cmd)
		free_matrix(node->data->com->cmd, node->data->com->matrix_size);
	free(node->data->com);
	free(node->data);
	free(node);
	return (tmp);
}

void	free_tree(t_trunk *tree)
{
	t_node	*node;
	t_node	*tmp;

	node = NULL;
	tmp = NULL;
	node = tree->leafs;
	while (node)
	{
		if (node && node->type == N_CMD)
			tmp = free_cmd(node);
		else if (node && node->type == N_PIPE)
		{
			tmp = node->data->pip->prev;
			if (node->data->pip->out)
				free_cmd(node->data->pip->out);
			free(node->data->pip);
			free(node->data);
			free(node);
		}
		node = tmp;
	}
	free_trunk_root(tree);
	free(tree);
}
