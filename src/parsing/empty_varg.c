/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_varg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 12:12:11 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/22 12:54:15 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

t_env	*empty_varg(t_env *head)
{
	char	pwd[1024];
	char	*cwd;

	cwd = getcwd(pwd, sizeof(pwd));
	head = (t_env *)malloc(sizeof(t_env));
	if (!head)
		return (NULL);
	head->name = wrt("PWD");
	head->data = wrt(cwd);
	head->prev = NULL;
	head->next = NULL;
	head->next = (t_env *)malloc(sizeof(t_env));
	if (!head->next)
		free_env(head);
	head->next->name = wrt("SHLVL");
	head->next->data = wrt("1");
	head->next->prev = head;
	head->next->next = NULL;
	head->next->next = (t_env *)malloc(sizeof(t_env));
	end_varg(head);
	return (head);
}

char	*wrt(char *to)
{
	char	*r;
	char	*t;

	r = (char *)malloc(sizeof(char) * (ft_strlen(to) + 1));
	if (!r)
		return (NULL);
	t = r;
	while (*to)
		*r++ = *to++;
	*r = '\0';
	return (t);
}

void	end_varg(t_env *head)
{
	if (!head->next->next)
		free_env(head);
	head->next->next->name = wrt("_");
	head->next->next->data = wrt("/usr/bin/env");
	head->next->next->next = NULL;
	head->next->next->prev = head->next;
}
