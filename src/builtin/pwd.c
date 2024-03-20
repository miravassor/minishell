/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:23:16 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/22 12:51:11 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

void	getcwd_error(char *error)
{
	ft_putstr_fd(error, 2);
	ft_putstr_fd(": error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
}

int	ft_pwd(void)
{
	char	pwd[1024];
	char	*cwd;

	cwd = getcwd(pwd, sizeof(pwd));
	if (!cwd)
	{
		getcwd_error("pwd");
		g_status = 1;
		return (1);
	}
	ft_putstr_fd(cwd, 1);
	write(1, "\n", 1);
	g_status = 0;
	return (0);
}
