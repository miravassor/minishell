/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:18:55 by mira              #+#    #+#             */
/*   Updated: 2023/03/24 11:40:01 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

void	tkn_add_back(t_tkn *head, t_tkn *new)
{
	t_tkn	*tmp;

	tmp = head;
	if (head)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	tmp->next = new;
}

int	add_find_id(t_lxr *lxr, t_lxid id)
{
	int	find;

	find = find_id(lxr, id) + 1;
	if (find <= 1)
		return (-1);
	else
	{
		lxr->pos--;
		while (find--)
			add_buff(lxr, next_chr(lxr));
	}
	lxr->prev_id = id;
	return (0);
}

int	add_end(t_lxr *lxr, t_lxid id)
{
	(void)id;
	free(lxr->buff);
	lxr->prev_id = END;
	return (EOT);
}

int	skip_trig(t_lxr *lxr, t_lxid id)
{
	(void)lxr;
	(void)id;
	lxr->prev_id = CSPACE;
	add_buff(lxr, ' ');
	return (0);
}

int	nomtch(t_lxr *lxr, t_lxid id)
{
	(void)lxr;
	(void)id;
	lxr->prev_id = NOMTCH;
	return (-2);
}
