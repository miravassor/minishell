/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanr_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:54:30 by avassor           #+#    #+#             */
/*   Updated: 2023/04/22 10:36:45 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

_Bool	buff_err(char *buff)
{
	size_t	i;

	i = 0;
	if (buff && buff[0] && buff[0] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
		g_status = 2;
		return (1);
	}
	return (buff_r1(buff, i));
}

size_t	chk_opp(char *tmp)
{
	size_t	sig;
	size_t	pp;
	size_t	i;

	sig = 0;
	pp = 0;
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] != '|' && tmp[i] != ' ')
			sig += 1;
		else if (tmp[i] == '|')
			pp += 1;
		i++;
	}
	if (sig && chk_op1(tmp, i))
		return (1);
	else if (!sig)
		return (chk_op2(pp));
	return (0);
}

size_t	chk_op1(char *tmp, size_t i)
{
	size_t	set;

	i = 0;
	set = 0;
	while (tmp[i] != '|')
	{
		if (tmp[i] != ' ')
		{
			set = 1;
			break ;
		}
		i++;
	}
	if (!set)
	{
		write(2, "minishell: syntax error near unexpected token `|'\n",
			51);
		g_status = 2;
		return (1);
	}
	return (0);
}

size_t	chk_op2(size_t pp)
{
	if (pp > 1)
		write(2, "minishell: syntax error near unexpected token `||'\n",
			52);
	else if (pp == 1)
		write(2, "minishell: syntax error near unexpected token `|'\n",
			51);
	g_status = 2;
	return (1);
}
