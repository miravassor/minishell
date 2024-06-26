/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:58:15 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/22 10:56:24 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_freetab(char **str, int size)
{
	while (str[size] != NULL)
	{
		free(str[size]);
		size--;
	}
	return (-1);
}

static int	ft_countword(char const *s, char set)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if ((s[i + 1] == set || s[i + 1] == '\0') == 1
			&& (s[i] == set || s[i] == '\0') == 0)
			word++;
		i++;
	}
	return (word);
}

static void	ft_writeword(char *dest, char const *src, char set)
{
	int	i;

	i = 0;
	while ((src[i] == set || src[i] == '\0') == 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static int	ft_splitword(char **tab, char const *str, char set)
{
	int	i;
	int	j;
	int	word;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == set || str[i] == '\0') == 1)
			i++;
		else
		{
			j = 0;
			while ((str[i + j] == set || str[i + j] == '\0') == 0)
				j++;
			tab[word] = (char *)malloc(sizeof(char) * (j + 1));
			if (!tab[word])
				return (ft_freetab(tab, word - 1));
			ft_writeword(tab[word], str + i, set);
			i += j;
			word++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		word;

	word = ft_countword(s, c);
	tab = (char **)malloc(sizeof(char *) * (word + 1));
	if (!(tab))
		return (NULL);
	tab[word] = 0;
	if (ft_splitword(tab, s, c) == -1)
		return (NULL);
	return (tab);
}
