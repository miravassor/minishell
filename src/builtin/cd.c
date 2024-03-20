/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:46:39 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/21 22:58:30 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

static char	*get_home(char *env, t_lcmd *cmd)
{
	char	*tmp;
	char	*tmpp;

	tmp = NULL;
	tmpp = NULL;
	if (cmd)
	{
		if (cmd->next == NULL)
			return (NULL);
		tmp = ft_strjoin(env, "/");
		tmpp = ft_strjoin(tmp, cmd->next->data + 1);
		free(tmp);
	}
	return (tmpp);
}

static char	*get_cd_env(t_lcmd *cmd)
{
	char	*tmp;
	char	*tmpp;
	char	*curr_rep;
	char	cd[1024];

	curr_rep = getcwd(cd, sizeof(cd));
	if (cmd->next == NULL)
		return (NULL);
	if (curr_rep)
	{
		tmp = ft_strjoin(curr_rep, "/");
		tmpp = ft_strjoin(tmp, cmd->next->data);
		free(tmp);
		return (tmpp);
	}
	return (NULL);
}

static int	ft_cd_3(t_lcmd *cmd)
{
	char	*root;
	char	*cd_env;

	cd_env = get_cd_env(cmd);
	root = NULL;
	if (cmd->next->data[0] == '/')
	{
		root = get_home("/", cmd);
		if (chdir(root) == -1)
			return_error(cmd->next->data, " : No such file or directory\n", 1);
	}
	else if (cd_env != NULL)
	{
		if (chdir(cd_env) == -1)
		{
			free(cd_env);
			return (return_error(cmd->next->data,
					" : No such file or directory\n", 1));
		}
		if (cd_env)
			free(cd_env);
		return (0);
	}
	free_cd(root, cd_env);
	return (0);
}

static int	ft_cd_2(t_excmd *curr, t_exec *exec)
{
	t_lcmd	*cmd;

	g_status = 0;
	cmd = curr->cmd;
	if (count_cmd(curr) > 2)
	{
		return_error(cmd->data, ": too much arguments\n", 1);
		return (1);
	}
	else if (ft_strcomp(cmd->data, "cd") && cmd->next->data[0] == '-')
	{
		printf("%s\n", ft_getenv_data(exec, "HOME"));
		if (chdir((ft_getenv_data(exec, "OLDPWD"))) == -1)
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (0);
	}
	else
		ft_cd_3(cmd);
	return (0);
}

int	ft_cd_1(t_excmd *curr, t_exec *exec)
{
	t_lcmd	*cmd;
	char	*home;

	cmd = curr->cmd;
	if (ft_strcomp(cmd->data, "cd/") || ft_strcomp(cmd->data, "cd~"))
		return_error(cmd->data, ": No such file or directory\n", 127);
	else if ((ft_strcomp(cmd->data, "cd") && count_cmd(curr) == 1))
		chdir(ft_getenv_data(exec, "OLDPWD"));
	else if (ft_strchr(cmd->next->data, '~'))
	{
		home = get_home(ft_getenv_data(exec, "HOME"), cmd);
		if (chdir(home) == -1)
		{
			g_status = 1;
			free(home);
			return (-1);
		}
		free(home);
	}
	else
		ft_cd_2(curr, exec);
	return (0);
}
