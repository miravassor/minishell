/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:46:01 by mira              #+#    #+#             */
/*   Updated: 2023/04/20 13:25:57 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

_Bool	group_cmd(t_node *cmd)
{
	int		i;
	char	**ptr;

	while (cmd)
	{
		ptr = init_var(&i, cmd);
		while (i < (int)cmd->data->com->matrix_size)
		{
			i = groupamargue(cmd, ptr, i);
			i++;
		}
		kill_sp(cmd, ptr);
		cmd = get_next_cmd_node(cmd);
	}
	return (0);
}

void	kill_sp(t_node *cmd, char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr && i < cmd->data->com->matrix_size)
	{
		if (ptr[i] && ptr[i][0] == ' ')
		{
			free(ptr[i]);
			ptr[i] = NULL;
		}
		i++;
	}
}

int	groupamargue(t_node *cmd, char **ptr, int i)
{
	if (ptr[i] && (ptr[i][0] == ' '))
		;
	else if (ptr[i] && ptr[i + 1] && ptr[i + 1][0] != ' '
		&& ptr[i + 1][0] != '<' && ptr[i + 1][0] != '>'
		&& ptr[i][0] != '<' && ptr[i][0] != '>')
	{
		ptr[i] = join_cmd(ptr[i], ptr[i + 1]);
		ptr[i + 1] = NULL;
		update_indexes(cmd);
		i = -1;
	}
	return (i);
}

void	clear_null(t_node *cmd)
{
	char	**ptr;
	int		i;

	while (cmd)
	{
		ptr = init_var(&i, cmd);
		while (ptr && i < (int)cmd->data->com->matrix_size)
		{
			if (!ptr[i])
			{
				free(ptr[i]);
				ptr[i] = NULL;
				update_indexes(cmd);
				i = -1;
			}
			i++;
		}
		cmd = get_next_cmd_node(cmd);
	}
}

char	*join_cmd(char *str1, char *str2)
{
	char	*join;
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen(str1) + ft_strlen(str2) + 1;
	join = (char *)malloc(sizeof(char) * i);
	if (!join)
		return (NULL);
	j = 0;
	k = 0;
	while (str1[j])
		join[k++] = str1[j++];
	j = 0;
	if (str2)
	{
		while (str2[j])
			join[k++] = str2[j++];
	}
	join[k] = '\0';
	free(str1);
	free(str2);
	return (join);
}
