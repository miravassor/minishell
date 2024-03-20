/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandr_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:27:29 by mira              #+#    #+#             */
/*   Updated: 2023/04/18 15:37:23 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

char	*clear_empty_env(char *dbl, char *tmp)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (&dbl[i] != tmp)
		i++;
	j = i;
	while (dbl[j] && (dbl[j] != ' ' && dbl[j] != '$' && dbl[j] != '\"'))
		j++;
	k = j;
	while (dbl[k])
		k++;
	new = (char *)malloc(sizeof(char) * (i + k - (j - i) + 1));
	if (!new)
		return (NULL);
	return (op_clear(new, dbl, i, j));
}

char	*op_clear(char *new, char *dbl, size_t i, size_t j)
{
	size_t	l;

	l = 0;
	while (l < (i - 1))
	{
		new[l] = dbl[l];
		l++;
	}
	while (dbl[j])
		new[l++] = dbl[j++];
	new[l] = '\0';
	return (new);
}

char	*delete_env(char *tmp, size_t i)
{
	char	*new;
	size_t	j;
	size_t	k;
	size_t	l;
	size_t	m;

	j = 1;
	l = 0;
	while (tmp[i + j] && tmp[i + j] != ' ' && tmp[i + j] != '$')
		j++;
	k = j;
	while (tmp[i + k])
		k++;
	l = ft_strlen(tmp) - j + k;
	new = (char *)malloc(sizeof(char) * (l + 1));
	if (!new)
		return (NULL);
	m = 0;
	m = op_del(new, tmp, m, i);
	while (j < k)
		new[m++] = tmp[j++];
	new[m] = '\0';
	free(tmp);
	return (new);
}

size_t	op_del(char *new, char *tmp, size_t m, size_t i)
{
	while (m <= i)
	{
		new[m] = tmp[m];
		m++;
	}
	return (m);
}
