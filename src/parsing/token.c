/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:43:42 by avassor           #+#    #+#             */
/*   Updated: 2023/04/19 17:40:55 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

int	add_buff(t_lxr *lxr, char c)
{
	lxr->data[++lxr->pos_data] = c;
	return (0);
}

int	add_buff_lim(t_lxr *lxr, t_lxid c)
{
	lxr->data[++lxr->pos_data] = (char)c;
	if (c != PIPE)
		if (prev_next_chr(lxr, lxr->pos) == lxr->data[lxr->pos_data])
			lxr->data[++lxr->pos_data] = next_chr(lxr);
	lxr->last_id = c;
	return (0);
}

t_tkn	*new_tkn(t_lxr *lxr, char *str, t_lxid id, t_tkn *tkn)
{
	t_tkn	*new;
	size_t	size;

	size = ft_strlen(str);
	if (size <= 0)
		return (NULL);
	new = (t_tkn *)malloc(sizeof(t_tkn));
	if (!new)
		return (rror(ENOMEM), NULL);
	new->data = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new->data)
		return (rror(ENOMEM), NULL);
	ft_strcpy(str, new->data, size);
	new->size = ft_strlen(new->data);
	new->id = 0;
	new->id = get_id(id, str);
	new->prev = NULL;
	new->prev = get_last_tkn(tkn);
	new->next = NULL;
	new->err = 0;
	if (init_buff(lxr))
		return (NULL);
	return (new);
}

t_tkn	*tknize(t_lxr *lxr)
{
	t_tkn	*head;
	char	next;
	int		sig;

	head = init_head(lxr);
	if (!head || init_buff(lxr))
		return (rror(ENOMEM), NULL);
	next = next_chr(lxr);
	while (lxr_id(next) != END)
	{
		if (lxr_id(next) >= CSPACE && lxr_id(next) != INTER)
		{
			sig = trig_char(head, lxr, lxr_id(next));
			if (sig < 0)
				return (NULL);
			if (lxr->pos_data >= 0)
				tkn_add_back(head, new_tkn(lxr, lxr->data, lxr->last_id, head));
		}
		else
			add_buff(lxr, next);
		next = next_chr(lxr);
	}
	tkn_add_back(head, new_tkn(lxr, lxr->data, lxr->last_id, head));
	return (head);
}

t_lxid	lxr_id(char c)
{
	if (c == ' ')
		return (CSPACE);
	if (c == '>')
		return (GREATR);
	if (c == '<')
		return (LESS);
	if (c == '|')
		return (PIPE);
	if (c == '\'')
		return (SMPLQUOT);
	if (c == '\"')
		return (DBLQUOT);
	if (c == '$')
		return (ENV);
	if (c == '\0')
		return (END);
	if (c == '?')
		return (INTER);
	else
		return (CHAR);
}
