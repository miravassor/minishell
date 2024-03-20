/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:07:46 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/22 10:54:27 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	char	*tab;
	size_t	size;

	size = 0;
	if (!s1 || !s2)
		return (NULL);
	if (s1)
		size += ft_strlen(s1);
	if (s2)
		size += ft_strlen(s2);
	newstr = malloc(sizeof(char) * (size + 1));
	if (!newstr)
		return (NULL);
	tab = newstr;
	while (*s1 != '\0')
		*newstr++ = *s1++;
	while (*s2 != '\0')
		*newstr++ = *s2++;
	*newstr = '\0';
	if (!tab)
		free(newstr);
	return (tab);
}
