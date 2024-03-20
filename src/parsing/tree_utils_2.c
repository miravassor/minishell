/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:22:27 by avassor           #+#    #+#             */
/*   Updated: 2023/04/22 10:39:05 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

t_node_cmd	*build_cmd(t_tkn *tkn)
{
	t_node_cmd	*ptr;

	ptr = (t_node_cmd *)malloc(sizeof(t_node_cmd));
	if (!ptr)
		return (rror(ENOMEM), NULL);
	ptr->cmd = NULL;
	ptr->pipe_parent = NULL;
	ptr->appen = 0;
	ptr->in = 0;
	ptr->out = 0;
	ptr->here_doc = 0;
	ptr->file = 0;
	ptr->path = 0;
	ptr->env = 0;
	ptr->matrix_size = 0;
	ptr->quotes = 0;
	ptr->excmd = NULL;
	ptr->state = 0;
	ptr->cmd = get_data(ptr, tkn);
	if (!ptr->cmd)
		return (free(ptr), NULL);
	if (ptr->appen || ptr->here_doc || ptr->in || ptr->out)
		ptr->file = 1;
	return (ptr);
}

t_tkn	*build_node(t_trunk *trunk, t_tkn *tkn)
{
	t_node	*new;

	new = NULL;
	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (rror(ENOMEM), NULL);
	new->data = NULL;
	new->type = N_CMD;
	new->data = (t_node_ptr *)malloc(sizeof(t_node_ptr));
	if (!new->data)
		return (free(new), rror(ENOMEM), NULL);
	new->data->com = NULL;
	new->data->com = build_cmd(tkn);
	if (!new->data->com)
		return (free(new->data), free(new), NULL);
	if (!trunk->an->pipe)
		trunk->leafs = new;
	else
		if (place_in_tree(trunk, new))
			return (NULL);
	return (get_next_tkn(tkn, PIPE));
}

_Bool	build_pipe(t_trunk *trunk)
{
	t_node	*new;
	t_node	*prev;

	new = (t_node *)malloc(sizeof(t_node));
	new->data = (t_node_ptr *)malloc(sizeof(t_node_ptr));
	new->data->pip = (t_node_pipe *)malloc(sizeof(t_node_pipe));
	if (!new || !new->data || !new->data->pip)
		return (rror(ENOMEM), 1);
	new->type = N_PIPE;
	new->data->pip->in = NULL;
	new->data->pip->out = NULL;
	new->data->pip->prev = NULL;
	if (trunk->leafs)
	{
		prev = trunk->leafs;
		prev->data->pip->prev = new;
		new->data->pip->in = prev;
		new->data->pip->out = NULL;
	}
	trunk->leafs = new;
	return (0);
}

_Bool	place_in_tree(t_trunk *trunk, t_node *node)
{
	if (trunk->leafs && !(trunk->leafs->data->pip->in))
			trunk->leafs->data->pip->in = node;
	else if (trunk->leafs && !(trunk->leafs->data->pip->out))
		trunk->leafs->data->pip->out = node;
	else
	{
		if (build_pipe(trunk) || place_in_tree(trunk, node))
			return (1);
	}
	node->data->com->pipe_parent = trunk->leafs;
	return (0);
}

size_t	get_matrix_size(t_tkn *tkn)
{
	size_t	size;

	size = 0;
	while (tkn && tkn->id != PIPE && tkn->id != END)
	{
		tkn = tkn->next;
		size++;
	}
	return (size);
}
