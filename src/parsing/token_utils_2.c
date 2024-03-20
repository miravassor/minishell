/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:18:55 by mira              #+#    #+#             */
/*   Updated: 2023/04/21 13:18:29 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

t_tkn	*get_last_tkn(t_tkn *tkn)
{
	t_tkn	*ptr;

	ptr = tkn;
	if (!ptr)
		return (NULL);
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

int	add_path(t_lxr *lxr, t_lxid id)
{
	(void)id;
	lxr->pos--;
	while (prev_next_chr(lxr, lxr->pos) != END
		&& (lxr_id(prev_next_chr(lxr, lxr->pos)) != CSPACE))
		add_buff(lxr, next_chr(lxr));
	return (0);
	lxr->prev_id = id;
	return (1);
}

int	add_env(t_lxr *lxr, t_lxid id)
{
	(void)id;
	lxr->pos--;
	add_buff(lxr, next_chr(lxr));
	while (prev_next_chr(lxr, lxr->pos) != END
		&& (lxr_id(prev_next_chr(lxr, lxr->pos)) != CSPACE
			&& (lxr_id(prev_next_chr(lxr, lxr->pos) != DBLQUOT)
				&& (lxr_id(prev_next_chr(lxr, lxr->pos)) != SMPLQUOT)
				&& (lxr_id(prev_next_chr(lxr, lxr->pos)) != ENV))))
		add_buff(lxr, next_chr(lxr));
	lxr->prev_id = ENV;
	return (0);
}

size_t	chk_osp(char *line)
{
	char	*tmp;

	tmp = line;
	while (*line)
	{
		if (*line != ' ')
			return (chk_opp(tmp));
		line++;
	}
	g_status = 2;
	return (1);
}

t_lxid	get_id(t_lxid id, char *str)
{
	if (id == PIPE && str && str[0] != '|')
		return (CHAR);
	else
		return (id);
}
