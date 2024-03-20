/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 22:57:19 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/21 22:57:50 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

size_t	search_str(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	count_cmd(t_excmd *curr)
{
	int		i;
	t_lcmd	*cmd;

	i = 0;
	cmd = curr->cmd;
	while (cmd != NULL)
	{
		if (*cmd->data == ' ')
			i--;
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int	numlen(long long int val)
{
	int	i;

	i = 0;
	if (val == LONG_MIN)
		return (20);
	if (val < 0)
	{
		i++;
		val *= -1;
	}
	while (val > 0)
	{
		if (val == 0)
			break ;
		val /= 10;
		i++;
	}
	return (i);
}

long long int	ft_atol(const char *value)
{
	long long int	res;
	long long int	neg;

	res = 0;
	neg = 1;
	while (*value == 32 || (*value >= 7 && *value <= 13))
		value++;
	if (*value == '-' || *value == '+')
	{
		if (*value == '-')
			neg = -1;
		value++;
	}
	while (*value && (*value >= '0' && *value <= '9'))
	{
		res = res * 10 + *value - '0';
		value++;
	}
	return (res * neg);
}

int	is_numeric(char *str)
{
	if (numlen(ft_atol(str)) == (int)ft_strlen(str))
		return (1);
	return (0);
}
