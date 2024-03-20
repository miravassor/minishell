/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rror.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:07:02 by avassor           #+#    #+#             */
/*   Updated: 2023/04/22 11:06:54 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

void	rror(int r_no)
{
	if (r_no == SYNTAX)
	{
		write(2, "syntax error near unexpected token `newline'\n", 46);
		g_status = 2;
		return ;
	}
	else if (r_no == EXPORTVAR)
	{
		write(2, "export: not a valid identifier\n",
			32);
		g_status = 1;
	}
	else if (r_no == 134)
		return_error(".", ": filename argument required\n", 2);
	else if (r_no)
		printf("%s\n", strerror(r_no));
	else
		printf("%s\n", strerror(errno));
	return ;
}

void	rrdir(_Bool i)
{
	if (i)
		write(2, "minishell: syntax error near unexpected token `newline'\n",
			57);
	else
		write(2, "minishell: syntax error near unexpected token `newline'\n",
			57);
	g_status = 2;
}
