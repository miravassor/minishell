/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_empty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:13:53 by mira              #+#    #+#             */
/*   Updated: 2023/04/17 18:08:58 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

char	**init_var(int *i, t_node *cmd)
{
	*i = 0;
	return (cmd->data->com->cmd);
}

_Bool	swap_array(t_node *cmd, int i)
{
	char	**tmp;
	char	**tmp2;

	tmp2 = cmd->data->com->cmd;
	tmp = delete_dim(cmd, i);
	if (!tmp)
		return (1);
	free_matrix(tmp2, cmd->data->com->matrix_size);
	cmd->data->com->cmd = tmp;
	cmd->data->com->matrix_size -= 1;
	if (!cmd->data->com->matrix_size)
	{
		free_matrix(cmd->data->com->cmd, 1);
		cmd->data->com->cmd = NULL;
	}
	return (0);
}

char	**delete_dim(t_node *cmd, size_t i)
{
	char	**new;
	char	**ptr;
	int		j;
	int		k;

	j = 0;
	k = 0;
	new = NULL;
	ptr = NULL;
	ptr = cmd->data->com->cmd;
	new = (char **)malloc(sizeof(char *) * (cmd->data->com->matrix_size));
	if (!new)
		return (rror(ENOMEM), NULL);
	new[cmd->data->com->matrix_size - 1] = NULL;
	while (k < (int)(cmd->data->com->matrix_size))
	{
		if (k == (int)i)
			k++;
		new[j] = add_to_matrix(ptr[k]);
		j++;
		k++;
	}
	return (new);
}
