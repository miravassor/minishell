/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanr_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:54:30 by avassor           #+#    #+#             */
/*   Updated: 2023/04/22 10:37:09 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

size_t	cleanr(t_trunk *tree, t_tkn *tkn, t_lxr *lxr)
{
	if (lxr)
	{
		if (lxr->buff)
			free(lxr->buff);
		if (lxr->data)
			free(lxr->data);
		free(lxr);
	}
	if (tkn)
		free_tkn(tkn);
	if (tree)
		free_tree(tree);
	return (0);
}

void	prer(size_t id)
{
	if (id == 1)
		write(2, "minishell: syntax error near unexpected token `||'\n", 52);
	if (id == 2)
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
	if (id == 3)
		write(2, "minishell: syntax error near unexpected token `newline'\n",
			57);
}

_Bool	buff_r1(char *buff, int i)
{
	while (buff && buff[i])
	{
		if (buff[i] == '|' && buff[i + 1] && buff[i + 1] == '|')
		{
			if (buff[i + 2] && buff[i + 2] == '|')
				prer(1);
			else
				prer(2);
			g_status = 2;
			return (1);
		}
		else if ((buff[i] == '<' || buff[i] == '>') && !buff[i + 1])
		{
			prer(3);
			g_status = 2;
			return (1);
		}
		i++;
	}
	return (0);
}
