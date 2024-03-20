/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:36:30 by mira              #+#    #+#             */
/*   Updated: 2023/04/18 15:40:30 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

_Bool	ft_export(t_exec *exec, t_excmd *excmd)
{
	t_lcmd	*cmd;
	char	*name;
	char	*data;

	cmd = excmd->cmd;
	name = NULL;
	data = NULL;
	if (!cmd->next)
		return (print_env(exec));
	if (chk_equal(cmd))
		return (rror(EXPORTVAR), 0);
	name = export_name(cmd->next->data);
	if (!name)
		return (0);
	data = export_data(cmd->next->data);
	if (!data)
	{
		if (name)
			free(name);
		return (0);
	}
	return (do_export(exec, cmd->next, name, data));
}

_Bool	chk_env_name(char *name, t_env *envp)
{
	while (envp)
	{
		if (!ft_sprstrncmp(name, envp->name))
			return (1);
		envp = envp->next;
	}
	return (0);
}

char	*export_data(char *cmd)
{
	char	*data;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	data = NULL;
	while (cmd[i] != '=')
		i++;
	i += 1;
	while (cmd[j])
		j++;
	k = j - i + 1;
	data = fill_data(cmd, i, j, &k);
	return (data);
}

char	*export_name(char *cmd)
{
	char	*id;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	id = NULL;
	while (cmd[j] != '=')
		j++;
	id = (char *)malloc(sizeof(char) * (j + 1));
	if (!id)
		return (rror(ENOMEM), NULL);
	id[j] = '\0';
	while (i < j)
	{
		id[i] = cmd[i];
		i++;
	}
	return (id);
}

char	*fill_data(char *cmd, size_t i, size_t j, size_t *k)
{
	char	*data;

	data = NULL;
	data = (char *)malloc(sizeof(char) * (*k));
	if (!data)
		return (rror(ENOMEM), NULL);
	*k = 0;
	while (i < j)
	{
		data[*k] = cmd[i++];
		*k += 1;
	}
	data[*k] = '\0';
	return (data);
}
