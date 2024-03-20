/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:04:11 by mira              #+#    #+#             */
/*   Updated: 2023/04/11 18:12:08 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

size_t	line_chk2(char *a, char *b)
{
	char	*p1;
	char	*p2;

	p1 = a;
	p2 = b;
	while (*p1 && *p1 != '\n')
	{
		if (*p2 && *p1 == *p2)
		{
			p1++;
			p2++;
		}
		else
			return (0);
	}
	return (1);
}

char	*limited(t_stash **stash, char *line, int fd)
{
	if (stash)
		ft_unleash(stash[fd]);
	stash[fd] = NULL;
	free(line);
	return (NULL);
}
