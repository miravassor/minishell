/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:29:22 by mira              #+#    #+#             */
/*   Updated: 2023/04/22 12:58:51 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

char	*find_env_data(char *envp)
{
	char	*out;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	j = i;
	while (envp[j])
		j++;
	out = (char *)malloc(sizeof(char) * (j - i));
	if (!out)
		return (NULL);
	while ((i + 1) < j)
	{
		out[k] = envp[i + 1];
		i++;
		k++;
	}
	out[k] = '\0';
	return (out);
}

t_env	*extract_env(char *env)
{
	t_env	*new;
	char	*tmp;
	size_t	i;

	i = 0;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = NULL;
	new->data = NULL;
	new->next = NULL;
	new->prev = NULL;
	tmp = find_env_name(env);
	i = ft_strlen(tmp);
	new->name = (char *)malloc(sizeof(char) * (i + 1));
	if (!new->name)
		return (free(tmp), NULL);
	ft_strcpy(tmp, new->name, ft_strlen(tmp));
	free(tmp);
	new->data = find_env_data(env);
	return (new);
}

t_env	*build_env(char **envp)
{
	t_env	*head;
	t_env	*new;
	size_t	i;

	i = 0;
	head = NULL;
	if (!*envp)
		return (empty_varg(head));
	head = extract_env(envp[i++]);
	if (!head)
		return (NULL);
	while (envp[i])
	{
		new = get_last_env(head);
		new->next = extract_env(envp[i]);
		new->next->prev = new;
		i++;
	}
	return (head);
}

t_env	*get_last_env(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	free_env(t_env *head)
{
	t_env	*tmp;
	t_env	*nxt;

	tmp = head->next;
	while (tmp)
	{
		nxt = tmp->next;
		free(tmp->data);
		free(tmp->name);
		free(tmp);
		tmp = nxt;
	}
	free(head->data);
	free(head->name);
	free(head);
}
