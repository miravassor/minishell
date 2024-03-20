/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:36:26 by mira              #+#    #+#             */
/*   Updated: 2023/04/18 15:40:12 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

_Bool	chk_equal(t_lcmd *cmd)
{
	char	*ptr;
	size_t	i;

	if (!cmd->next || !cmd->next->data)
		return (1);
	ptr = cmd->next->data;
	i = 0;
	while (ptr[i])
	{
		while (ptr[i] && ptr[i] == ' ')
			i++;
		while (ptr[i] && ptr[i] != '=' && ptr[i] != ' ' && ptr[i] != '+')
			i++;
		if (ptr[i] && ptr[i] == '=')
			return (0);
		return (1);
	}
	return (1);
}

_Bool	chk_equal2(t_lcmd *cmd)
{
	char	*ptr;
	size_t	i;

	if (!cmd->data)
		return (1);
	ptr = cmd->data;
	i = 0;
	while (ptr[i])
	{
		while (ptr[i] && ptr[i] == ' ')
			i++;
		while (ptr[i] && ptr[i] != '=' && ptr[i] != ' ' && ptr[i] != '+')
			i++;
		if (ptr[i] && ptr[i] == '=')
			return (0);
		return (1);
	}
	return (1);
}

_Bool	add_env_list(t_env *envp, char *name, char *data)
{
	t_env	*new;

	new = NULL;
	while (envp->next)
		envp = envp->next;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->prev = NULL;
	new->name = NULL;
	new->data = NULL;
	new->next = NULL;
	new->prev = envp;
	new->name = name;
	new->data = data;
	envp->next = new;
	return (0);
}

_Bool	do_export(t_exec *exec, t_lcmd *cmd, char *name, char *data)
{
	t_env	*env;

	env = exec->envp;
	if (!(chk_env_name(name, exec->envp)))
	{
		if (add_env_list(exec->envp, name, data))
			return (1);
	}
	else
	{
		while (ft_sprstrncmp(name, env->name))
			env = env->next;
		free(env->data);
		env->data = NULL;
		env->data = data;
		free(name);
	}
	if (cmd->next)
		follow_export(exec, cmd->next);
	return (0);
}

void	follow_export(t_exec *exec, t_lcmd *cmd)
{
	char	*name;
	char	*data;

	name = NULL;
	data = NULL;
	if (!chk_equal2(cmd))
	{
		name = export_name(cmd->data);
		if (name)
		{
			data = export_data(cmd->data);
			if (!data)
			{
				if (name)
					free(name);
			}
			do_export(exec, cmd, name, data);
		}
	}
}
