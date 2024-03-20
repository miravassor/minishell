/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:33:44 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/22 11:39:49 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

static	void	back_slash(int sig)
{
	g_status = 131;
	printf("Quit (core dumped)\n");
	(void) sig;
}

static	void	hd_sig(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		g_status = 130;
	}
	if (sig == SIGQUIT)
		back_slash(sig);
}

void	hd_sig_line(int nb)
{
	signal(SIGINT, hd_sig);
	(void) nb;
	g_status = 130;
}

static	void	ctrl_c(int sig)
{
	(void) sig;
	g_status = 130;
}

int	run_signals(int sig)
{
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 4)
	{
		signal(SIGINT, hd_sig);
		signal(SIGQUIT, hd_sig);
	}
	if (sig == 5)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	return (0);
}
