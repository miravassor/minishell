/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:53:37 by avassor           #+#    #+#             */
/*   Updated: 2023/04/13 12:09:02 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

char	*ft_realloc(char *in, int size)
{
	char	*tmp;
	int		pos;

	tmp = (char *)malloc(sizeof(char) * size);
	if (!tmp)
		rror(ENOMEM);
	pos = 0;
	while (in[pos])
	{
		tmp[pos] = in[pos];
		pos++;
	}
	while (pos <= (size - 1))
	{
		tmp[pos] = '\0';
		pos++;
	}
	return (tmp);
}

void	ft_strcpy(char *in, char *out, size_t size)
{
	size_t	pos;

	pos = 0;
	while (pos < size)
	{
		out[pos] = in[pos];
		pos++;
	}
	out[pos] = '\0';
}

void	ft_nullset(char *in, int size)
{
	int	pos;

	pos = 0;
	while (pos <= size)
	{
		in[pos] = '\0';
		pos++;
	}
}

char	*find_env_name(char *envp)
{
	char	*out;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	out = (char *)malloc(sizeof(char) * (i + 1));
	if (!out)
		return (NULL);
	while (j < i)
	{
		out[j] = envp[j];
		j++;
	}
	out[j] = '\0';
	return (out);
}

char	*catch_env(t_env *envp, char *env)
{
	char	*tmp;

	while (envp)
	{
		tmp = envp->name;
		if (!tmp)
			return (NULL);
		if (!ft_sprstrncmp(env, tmp))
			return (envp->data);
		envp = envp->next;
	}
	return (NULL);
}
