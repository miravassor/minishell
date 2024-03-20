/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:30:54 by mira              #+#    #+#             */
/*   Updated: 2023/04/19 16:15:21 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

int	trig_char(t_tkn *head, t_lxr *lxr, t_lxid id)
{
	int	(*fptr[129])(t_lxr *, t_lxid);

	fptr[CSPACE] = skip_trig;
	fptr[GREATR] = add_buff_lim;
	fptr[LESS] = add_buff_lim;
	fptr[PIPE] = add_buff_lim;
	fptr[SMPLQUOT] = add_find_id;
	fptr[DBLQUOT] = add_find_id;
	fptr[DOT] = add_path;
	fptr[SLASH] = add_path;
	fptr[ENV] = add_env;
	fptr[END] = add_end;
	fptr[NOMTCH] = nomtch;
	if (lxr->pos_data > -1)
		tkn_add_back(head, new_tkn(lxr, lxr->data, lxr->last_id, head));
	lxr->last_id = id;
	return (((*fptr[id])(lxr, id)));
}

int	find_id(t_lxr *lxr, t_lxid id)
{
	char	c;
	int		count;

	count = lxr->pos;
	c = prev_next_chr(lxr, count);
	while (c != END && c != id)
		c = prev_next_chr(lxr, ++count);
	return ((count - lxr->pos + 1));
}

int	init_buff(t_lxr *lxr)
{
	if (lxr->data)
		free(lxr->data);
	lxr->pos_data = -1;
	lxr->data = (char *)malloc(sizeof(char) * lxr->size + 1);
	if (!lxr->data)
		return (1);
	ft_nullset(lxr->data, lxr->size);
	return (0);
}

t_tkn	*init_head(t_lxr *lxr)
{
	t_tkn	*head;

	if (!lxr)
		return (NULL);
	head = (t_tkn *)malloc(sizeof(t_tkn));
	if (!head)
		rror(ENOMEM);
	head->data = NULL;
	head->size = 0;
	head->prev = NULL;
	head->next = NULL;
	head->id = HEAD;
	return (head);
}

size_t	check_even_id(char *str, t_lxid id)
{
	size_t	pos;
	size_t	res;

	pos = 0;
	res = 0;
	while (str[pos])
	{
		if (str[pos] == id)
			res++;
		pos++;
	}
	return (res % 2);
}
