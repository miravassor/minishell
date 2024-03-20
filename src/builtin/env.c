/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:47:16 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/22 12:41:24 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

_Bool	print_env(t_exec *exec)
{
	t_env	*envp;

	envp = exec->envp;
	while (envp)
	{
		printf("%s=%s\n", envp->name, envp->data);
		envp = envp->next;
	}
	return (0);
}
