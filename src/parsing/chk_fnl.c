/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_fnl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:25:08 by mira              #+#    #+#             */
/*   Updated: 2023/04/21 22:27:53 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

_Bool	chk_fnl(t_node *cmd)
{
	while (cmd)
	{
		chk_fcmd(cmd);
		cmd = get_next_cmd_node(cmd);
	}
	return (0);
}

_Bool	chk_fcmd(t_node *cmd)
{
	t_excmd	*curr;
	t_lcmd	*in;

	curr = cmd->data->com->excmd;
	if (curr->in)
	{
		in = curr->in;
		while (in)
		{
			if (chk_ill(in->data, '.'))
				del_chr(in->data, '.');
			if (chk_ill(in->data, '/'))
				del_chr(in->data, '/');
			chk_ill2(in->data);
			in = in->next;
		}
	}
	return (0);
}

_Bool	chk_ill(char *data, char c)
{
	while (*data && *data == '<')
		data++;
	while (*data)
	{
		if (*data != c)
			return (0);
		data++;
	}
	return (1);
}

void	del_chr(char *data, char c)
{
	size_t	i;

	i = 0;
	while (data[i] && data[i] == '<')
		i++;
	while (data[i] && data[i] == c)
	{
		data[i] = '\0';
		i++;
	}
}

void	chk_ill2(char *data)
{
	if (data[0] && data[1] && data[1] == '.'
		&& data[2] && data[2] == '/')
	{
		data[1] = '\0';
		data[2] = '\0';
	}
}
