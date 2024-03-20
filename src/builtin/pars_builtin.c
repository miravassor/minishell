/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:35:10 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/21 16:42:53 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

_Bool	check_builtin(t_excmd *excmd)
{
	if (excmd->cmd && excmd->cmd->data)
	{
		if (ft_strncmp(excmd->cmd->data, "echo\0", 5) == 0)
			return (0);
		else if (ft_strncmp(excmd->cmd->data, "cd\0", 3) == 0)
			return (0);
		else if (ft_strncmp(excmd->cmd->data, "export\0", 7) == 0)
			return (0);
		else if (ft_strncmp(excmd->cmd->data, "exit\0", 5) == 0)
			return (0);
		else if (ft_strncmp(excmd->cmd->data, "pwd\0", 4) == 0)
			return (0);
		else if (ft_strncmp(excmd->cmd->data, "env\0", 4) == 0)
			return (0);
		else if (ft_strncmp(excmd->cmd->data, "unset\0", 6) == 0)
			return (0);
		else if (ft_strncmp(excmd->cmd->data, "$?\0", 3) == 0)
			return (0);
	}
	return (1);
}
