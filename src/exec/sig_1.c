/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:34:41 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/22 13:01:40 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

void	child_signal(int num)
{
	if (num == SIGINT)
		g_status = 130;
	if (num == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		g_status = 131;
	}
}

void	sig_clean(int nope)
{
	(void) nope;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = 130;
}

void	sig_init(void)
{
	signal(SIGINT, sig_clean);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_child(void)
{
	signal(SIGINT, child_signal);
	signal(SIGQUIT, child_signal);
}
