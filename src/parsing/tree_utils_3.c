/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:22:27 by avassor           #+#    #+#             */
/*   Updated: 2023/04/19 17:39:50 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

t_tkn	*get_next_tkn(t_tkn *tkn, t_lxid id)
{
	if (!tkn)
		return (NULL);
	while (tkn && tkn->id != id)
		tkn = tkn->next;
	if (tkn && tkn->id == id)
		return (tkn->next);
	return (NULL);
}

char	*init_string(int size)
{
	char	*new;

	new = (char *)malloc(sizeof(char) * (size + 2));
	if (!new)
		return (rror(ENOMEM), NULL);
	return (new);
}

char	*add_to_matrix(char *tkn)
{
	char	*new_data;
	char	*init;
	int		i;

	i = 0;
	i = ft_strlen(tkn);
	new_data = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_data)
		return (rror(ENOMEM), NULL);
	init = new_data;
	while (tkn && *tkn)
		*new_data++ = *tkn++;
	*new_data = '\0';
	return (init);
}

char	**get_data(t_node_cmd *cmd, t_tkn *tkn)
{
	char	**data;
	size_t	i;

	data = NULL;
	i = 0;
	i = get_matrix_size(tkn);
	if (!i)
		return (NULL);
	cmd->matrix_size = i;
	if (!i)
		return (NULL);
	data = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data)
		return (rror(ENOMEM), NULL);
	data[i] = NULL;
	i = 0;
	while (tkn && check_tkn_type(cmd, tkn))
	{
		data[i++] = add_to_matrix(tkn->data);
		if (i < cmd->matrix_size && !data[i - 1])
			return (NULL);
		tkn = tkn->next;
	}
	return (data);
}

size_t	check_redir(t_node_cmd *cmd, t_tkn *tkn)
{
	if (check_here(tkn))
	{
		cmd->here_doc = 1;
		return (1);
	}
	else if (check_in(tkn))
	{
		cmd->in = 1;
		return (0);
	}
	if (check_app(tkn))
	{
		cmd->appen = 1;
		return (1);
	}
	else if (check_out(tkn))
	{
		cmd->out = 1;
		return (0);
	}
	return (0);
}
