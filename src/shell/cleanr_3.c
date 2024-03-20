/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanr_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:54:30 by avassor           #+#    #+#             */
/*   Updated: 2023/04/21 19:20:49 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

void	free_list(t_excmd *excmd)
{
	if (excmd->in)
		free_link(excmd->in);
	if (excmd->out)
		free_link(excmd->out);
	if (excmd->cmd)
		free_link(excmd->cmd);
	free(excmd);
}

void	free_link(t_lcmd *list)
{
	t_lcmd	*tmp;

	while (list)
	{
		tmp = list->next;
		if (list->data)
			free(list->data);
		free(list);
		list = tmp;
	}
}

void	free_exec(t_exec *exec)
{
	if (exec->path)
		free_matrix(exec->path, get_matrix_2(exec->path));
	if (exec->fd)
		free(exec->fd);
	if (exec)
		free(exec);
	if (g_status == 139)
		g_status = 127;
}

void	good_bye(t_lxr *lxr, t_env *mini_env)
{
	rl_clear_history();
	if (lxr)
		cleanr(NULL, NULL, lxr);
	free_env(mini_env);
	printf("exit\n");
	exit (EXIT_SUCCESS);
}
