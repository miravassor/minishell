/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:22:27 by avassor           #+#    #+#             */
/*   Updated: 2023/04/19 11:54:33 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

_Bool	check_here(t_tkn *tkn)
{
	if (tkn->id == LESS)
	{
		if (tkn->next && tkn->next->id == LESS)
			return (1);
	}
	return (0);
}

_Bool	check_app(t_tkn *tkn)
{
	if (tkn->id == GREATR)
	{
		if (tkn->next && tkn->next->id == GREATR)
			return (1);
	}
	return (0);
}

_Bool	check_in(t_tkn *tkn)
{
	if (tkn->id == LESS)
		return (1);
	return (0);
}

_Bool	check_out(t_tkn *tkn)
{
	if (tkn->id == GREATR)
		return (1);
	return (0);
}

char	*expand_dbl(t_env *envp, char *ptr, char *tmp, char *rec)
{
	size_t	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '$')
		{
			if (ptr[i + 1] && ptr[i + 1] != '\"'
				&& ptr[i + 1] != '$' && ptr[i + 1] != '?')
			{
				rec = replace_env(tmp, &ptr[i + 1], envp);
				if (rec)
				{
					free(tmp);
					tmp = NULL;
					ptr = rec;
					tmp = rec;
					continue ;
				}
			}
		}
		i++;
	}
	return (tmp);
}
