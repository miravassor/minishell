/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:47:08 by mira              #+#    #+#             */
/*   Updated: 2023/04/21 22:39:12 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

char	*add_dir(char *content, char *cmd)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!content || !cmd)
		return (NULL);
	i = 0;
	j = ft_strlen(content) + 1;
	k = ft_strlen(cmd) + 1;
	str = (char *)malloc(sizeof(char) * (j + k + 1));
	if (!str)
		return (NULL);
	while (content[i])
	{
		str[i] = content[i];
		i++;
	}
	str[i] = '/';
	i = 0;
	while (cmd[i])
		str[j++] = cmd[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_getenv_data(t_exec *exec, char *id)
{
	t_env	*envp;

	envp = exec->envp;
	while (envp)
	{
		if (ft_strcomp(envp->name, id))
			return (envp->data);
		envp = envp->next;
	}
	return (NULL);
}

char	*get_system_path(t_exec *exec, char *cmd)
{
	char	**path;
	char	*full;
	size_t	i;

	path = exec->path;
	i = 0;
	if (!path)
		return (NULL);
	while (path[i])
	{
		full = add_dir(path[i], cmd);
		if (full)
		{
			if (!lstat(full, &exec->s_buf))
			{
				if (!has_perm(path, full, exec->s_buf))
					return (full);
			}
		}
		free(full);
		i++;
	}
	return (NULL);
}

char	*get_user_path(char *cmd, t_exec *exec)
{
	stat(cmd, &exec->s_buf);
	if (access(cmd, F_OK) >= 0)
	{
		if (!(cmd))
			return (NULL);
		if (S_ISDIR(exec->s_buf.st_mode))
			return (NULL);
		else
			return (cmd);
	}
	if (!access(cmd, F_OK) || !access(cmd, X_OK))
		return (cmd);
	return (NULL);
}

char	*get_path(t_exec *exec, char *cmd)
{
	char	*full;

	full = NULL;
	if (cmd && (cmd[0] == '/' || cmd[0] == '.'))
		full = get_user_path(cmd, exec);
	else
		full = get_system_path(exec, cmd);
	if (full == NULL)
		return (NULL);
	return (full);
}
