/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:19:28 by mira              #+#    #+#             */
/*   Updated: 2023/04/19 11:37:59 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

void	unquote(t_node *cmd)
{
	t_lcmd	*lcmd;

	while (cmd)
	{
		if (cmd->data->com->quotes)
		{
			lcmd = NULL;
			if (cmd->data->com->excmd)
				if (cmd->data->com->excmd->cmd)
					lcmd = cmd->data->com->excmd->cmd;
			if (lcmd)
				do_unquote(lcmd);
		}
		cmd = get_next_cmd_node(cmd);
	}
}

void	do_unquote(t_lcmd *lcmd)
{
	char	*ptr;
	int		i;

	ptr = NULL;
	while (lcmd)
	{
		i = 0;
		ptr = lcmd->data;
		while (ptr && ptr[i])
		{
			if ((ptr[i] && (ptr[i] == '\"' || ptr[i] == '\'')))
			{
				lcmd->data = remove_quote(lcmd->data);
				break ;
			}
			i++;
		}
		lcmd = lcmd->next;
	}
}

char	*remove_quote(char *cmd)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = ft_strlen(cmd) - 1;
	new = (char *)malloc(sizeof(char) * i);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] != '\"' && cmd[i] != '\'')
			new[j++] = cmd[i];
		i++;
	}
	new[j] = '\0';
	free(cmd);
	return (new);
}
