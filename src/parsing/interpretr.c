/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:09:47 by mira              #+#    #+#             */
/*   Updated: 2023/04/21 22:29:30 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

_Bool	interpretr(t_node *cmd)
{
	while (cmd)
	{
		if (build_link(cmd, cmd->data->com->cmd))
			return (1);
		update_heads(cmd);
		unquote(cmd);
		cmd = get_next_cmd_node(cmd);
	}
	return (0);
}

void	update_heads(t_node *cmd)
{
	t_lcmd	*keep;

	keep = cmd->data->com->excmd->in;
	if (keep)
	{
		cmd->data->com->excmd->in = cmd->data->com->excmd->in->next;
		cmd->data->com->excmd->in->prev = NULL;
		free(keep);
	}
	keep = cmd->data->com->excmd->out;
	if (keep)
	{
		cmd->data->com->excmd->out = cmd->data->com->excmd->out->next;
		cmd->data->com->excmd->out->prev = NULL;
		free(keep);
	}
	keep = cmd->data->com->excmd->cmd;
	if (keep)
	{
		cmd->data->com->excmd->cmd = cmd->data->com->excmd->cmd->next;
		cmd->data->com->excmd->cmd->prev = NULL;
		free(keep);
	}
}

void	get_status(t_excmd *head, char **cmd)
{
	if (cmd[0][0] == '<')
	{
		if (cmd[0][1] && cmd[0][1] == '<')
			head->heredoc = 1;
		else
			head->in_size = 1;
	}
	else if (cmd[0][0] == '>')
	{
		if (cmd[0][1] && cmd[0][1] == '>')
			head->appen = 1;
		else
			head->out_size = 1;
	}
}

_Bool	swap_index(t_lcmd *lcmd, char *in)
{
	t_lcmd	*new;
	t_lcmd	*get;

	new = init_lcmd(NULL, NULL);
	if (!new)
		return (rror(ENOMEM), 1);
	get = lcmd;
	while (get->next)
		get = get->next;
	get->prev = get;
	get->next = new;
	new->data = in;
	return (0);
}

size_t	add_to_list(t_lcmd *init, char **in)
{
	size_t	i;

	i = 0;
	if (swap_index(init, in[i++]))
		return (1);
	in[i - 1] = NULL;
	if (in[i] && in[i][0] && in[i][0] == ' ')
	{
		free(in[i++]);
		in[i - 1] = NULL;
	}
	return (0);
}
