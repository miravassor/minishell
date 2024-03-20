/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandr_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:15:06 by mira              #+#    #+#             */
/*   Updated: 2023/04/19 18:20:32 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

_Bool	do_expand(char **browse, t_env *envp)
{
	size_t	i;

	i = 0;
	while (browse[i])
	{
		if (browse[i][0] == '$' && browse[i][1] && browse[i][1] != '?')
			browse[i] = expand_env(browse[i], envp);
		else if (browse[i][0] == '$' && !browse[i][1] && browse[i + 1]
			&& (browse[i + 1][0] == '\"' || browse[i + 1][0] == '\''))
		{
			free(browse[i]);
			browse[i] = NULL;
		}
		else if (browse[i][0] == '\"')
			if (do_expand_dbl(browse, i, envp))
				return (1);
		i++;
	}
	return (0);
}

_Bool	do_expand_dbl(char **browse, size_t i, t_env *envp)
{
	char	*ctmp;

	ctmp = expand_dbl_quotes(browse[i], envp);
	browse[i] = ctmp;
	return (0);
}

t_node	*get_next_cmd_node(t_node *node)
{
	t_node	*ptr;
	t_node	*ptr2;

	if (node->type == N_CMD)
		ptr = node->data->com->pipe_parent;
	else
		ptr = node;
	if (!ptr)
		return (NULL);
	if (ptr->data->pip->out != node)
		return (ptr->data->pip->out);
	else
	{
		ptr2 = ptr->data->pip->prev;
		if (!ptr2)
			return (NULL);
		return (get_next_cmd_node(ptr2));
	}
}

char	*cut_env(char *env)
{
	size_t	size;
	size_t	i;
	char	*new_env;

	size = 0;
	i = 0;
	size++;
	while (env[size] && chk_chr(env[size]))
		size++;
	new_env = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_env)
		return (rror(ENOMEM), NULL);
	i = 0;
	while (env[i] && env[i] != ' ' && env[i] != '\"'
		&& env[i] != '$' && env[i] != '=')
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = '\0';
	return (new_env);
}

char	*empty_env(char *tmp)
{
	free(tmp);
	return (NULL);
}
