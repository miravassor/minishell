/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:43:57 by avassor           #+#    #+#             */
/*   Updated: 2023/04/17 20:20:59 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

char	prev_next_chr(t_lxr *lxr, int pos)
{
	int	npos;

	npos = pos + 1;
	if (npos >= lxr->size)
		return (END);
	return (lxr->buff[npos]);
}

char	prev_ious_chr(t_lxr *lxr, int pos)
{
	int	npos;

	npos = pos - 1;
	if (npos >= lxr->size)
		return (END);
	return (lxr->buff[npos]);
}

void	skip_wspaces(t_lxr *lxr)
{
	char	c;

	c = prev_next_chr(lxr, lxr->pos);
	while (c != END && (c == ' ' || c == '\t'))
		c = next_chr(lxr);
}

void	unget_chr(t_lxr *lxr)
{
	if (lxr->pos < 0)
		return ;
	lxr->pos--;
}

char	next_chr(t_lxr *lxr)
{
	if (++lxr->pos >= lxr->size)
	{
		lxr->pos = lxr->size;
		return ('\0');
	}
	return (lxr->buff[lxr->pos]);
}
