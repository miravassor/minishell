/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandr_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:27:58 by mira              #+#    #+#             */
/*   Updated: 2023/04/19 18:20:46 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

char	*expand_env(char *env, t_env *envp)
{
	char	*ptr;
	char	*tmp;
	char	*res;
	size_t	i;

	i = 0;
	res = NULL;
	tmp = cut_env(env + 1);
	ptr = catch_env(envp, tmp);
	if (!ptr)
		return (free(env), empty_env(tmp));
	i = ft_strlen(ptr);
	if (i)
	{
		res = (char *)malloc(sizeof(char) * (i + 1));
		if (!res)
			return (rror(ENOMEM), NULL);
		i = 0;
		while (*ptr)
			res[i++] = *ptr++;
		res[i] = '\0';
		free(tmp);
	}
	return (free(env), res);
}

char	*write_expand_env(char *dbl, char *env, char *ptr, size_t size)
{
	char	*out;
	size_t	size_dbl;
	size_t	size_env;
	size_t	i;
	size_t	j;

	size_dbl = ft_strlen(dbl);
	size_env = ft_strlen(env) + 1;
	i = 0;
	j = 0;
	out = (char *)malloc(sizeof(char) * ((size_dbl - (size + 1)) + size_env));
	if (!out)
		return (NULL);
	while (dbl[i] && &dbl[i + 1] != ptr)
		out[j++] = dbl[i++];
	i += size + 1;
	size_dbl = 0;
	while (env[size_dbl])
		out[j++] = env[size_dbl++];
	while (dbl[i])
		out[j++] = dbl[i++];
	out[j] = '\0';
	return (out);
}

char	*replace_env(char *dbl, char *ptr, t_env *envp)
{
	char	*env;
	char	*tmp_env;
	size_t	size;
	size_t	i;

	size = 0;
	while (ptr[size] && chk_chr(ptr[size]))
		size++;
	if (!size)
		return (NULL);
	tmp_env = (char *)malloc(sizeof(char) * (size + 1));
	if (!tmp_env)
		return (NULL);
	i = 0;
	while (ptr[i] && chk_chr(ptr[i]))
	{
		tmp_env[i] = ptr[i];
		i++;
	}
	tmp_env[i] = '\0';
	env = catch_env(envp, tmp_env);
	if (!env)
		return (free(tmp_env), clear_empty_env(dbl, ptr));
	return (free(tmp_env), write_expand_env(dbl, env, ptr, size));
}

char	*expand_dbl_quotes(char *dbl, t_env *envp)
{
	char	*ptr;
	char	*tmp;
	char	*rec;

	ptr = dbl;
	tmp = dbl;
	rec = NULL;
	tmp = expand_dbl(envp, ptr, tmp, rec);
	return (tmp);
}

_Bool	expandr(t_node *node, t_env *envp)
{
	t_node	*tmp;
	char	**browse;

	tmp = node;
	while (1)
	{
		if (node->data->com->cmd)
		{
			browse = node->data->com->cmd;
			if (do_expand(browse, envp))
				return (1);
		}
		node = get_next_cmd_node(node);
		if (!node || node == tmp)
			break ;
	}
	return (0);
}
