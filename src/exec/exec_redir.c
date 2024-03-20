/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:09:33 by mira              #+#    #+#             */
/*   Updated: 2023/04/21 22:52:50 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

char	*build_args(t_lcmd *lcmd, int i)
{
	char	*arg;
	int		count;
	size_t	j;

	count = 0;
	j = 0;
	while (count < i)
	{
		if (lcmd->data[0] == ' ')
				lcmd = lcmd->next;
		else
		{
			lcmd = lcmd->next;
			count++;
		}
	}
	j = ft_strlen(lcmd->data);
	arg = (char *)malloc(sizeof(char) * (j + 1));
	if (!arg)
		return (NULL);
	count = 0;
	j = 0;
	while (lcmd->data[j])
		arg[count++] = lcmd->data[j++];
	return (arg[count] = '\0', arg);
}

char	**get_args(t_excmd *curr, t_lcmd *lcmd)
{
	char	**args;
	char	*ptr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	args = NULL;
	while (lcmd)
	{
		ptr = lcmd->data;
		if (ptr && ptr[0] && ptr[0] != ' ')
			i++;
		lcmd = lcmd->next;
	}
	args = (char **)malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL);
	args[i] = NULL;
	while (j < i)
	{
		args[j] = build_args(curr->cmd, j);
		j++;
	}
	return (args);
}

int	no_such(char *str)
{
	printf("minishell: %s: No such file or directory\n", str);
	g_status = 1;
	return (-1);
}

void	close_fd(int fd, int ref)
{
	if (fd != ref)
		close(fd);
}
