/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 23:19:25 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/21 19:21:43 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

static void	ft_unsets(t_exec *exec, t_env *env)
{
	free(env->data);
	free(env->name);
	if (env->prev)
		env->prev->next = env->next;
	else
	{
		env->next->prev = NULL;
		exec->envp = env->next;
	}
	if (env->next)
		env->next->prev = env->prev;
	else
		env->prev->next = NULL;
	free(env);
}

int	ft_unset(t_exec *exec, t_excmd *curr)
{
	t_lcmd	*lcmd;
	t_env	*env;

	env = exec->envp;
	if (ft_strcomp(curr->cmd->data, "unset") && !curr->cmd->next)
		return (1);
	lcmd = curr->cmd->next;
	while (env && lcmd)
	{
		if (!ft_sprstrncmp(lcmd->data, env->name))
		{
			ft_unsets(exec, env);
			if (!lcmd->next)
				break ;
			else
			{
				env = exec->envp;
				lcmd = lcmd->next;
			}
		}
		env = env->next;
	}
	g_status = 0;
	return (0);
}
