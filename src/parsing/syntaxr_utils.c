/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:13:34 by mira              #+#    #+#             */
/*   Updated: 2023/04/19 16:41:16 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

size_t	illegal_redir(char *line)
{
	if (!line)
		return (1);
	if (!*line || *line == '|' || *line == '>' || *line == '<')
		return (1);
	return (0);
}

size_t	illegal_line(char *line)
{
	line++;
	if (*line == ' ' && *(line + 1) && (*(line + 1) == '<'
			|| *(line + 1) == '>'))
		return (1);
	return (0);
}

_Bool	chk_chr(char c)
{
	if (c == ' ')
		return (0);
	if (c == '\"')
		return (0);
	if (c == '$')
		return (0);
	if (c == '=')
		return (0);
	return (1);
}

_Bool	ft_sprstrncmp(char *s1, char *s2)
{
	while (*s1)
	{
		if (!*s2)
			return (1);
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	if (!*s1 && *s2 && *s2 != '\n')
		return (1);
	return (0);
}

void	clear_spaces(t_node *cmd)
{
	int		i;
	char	**ptr;

	while (cmd)
	{
		ptr = init_var(&i, cmd);
		while (i < (int)cmd->data->com->matrix_size)
		{
			if (ptr[i] && ptr[i][0] == ' ' && !ptr[i][1])
			{
				i++;
				if (i >= (int)cmd->data->com->matrix_size)
				{
					free(ptr[i - 1]);
					ptr[i - 1] = NULL;
					cmd->data->com->matrix_size -= 1;
					break ;
				}
				i = clearrr(cmd, ptr, i);
			}
			i++;
		}
		cmd = get_next_cmd_node(cmd);
	}
}
