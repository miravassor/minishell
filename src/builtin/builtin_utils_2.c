/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:26:45 by mira              #+#    #+#             */
/*   Updated: 2023/04/21 22:57:55 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

int	return_code(void)
{
	printf("%d : command not found\n", g_status);
	return (0);
}

void	free_cd(char *root, char *cd_env)
{
	if (cd_env)
		free(cd_env);
	if (root)
		free(root);
}
