/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretr_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:38:30 by mira              #+#    #+#             */
/*   Updated: 2023/04/19 18:24:39 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

t_lcmd	*extract_data(t_excmd *head, char **cmd, char c, size_t msize)
{
	t_lcmd	*init;
	char	**ptr;
	_Bool	sig;
	size_t	i;

	init = init_lcmd(&i, &sig);
	if (!init)
		return (head->enomem = 1, rror(ENOMEM), NULL);
	ptr = cmd;
	while (i < msize)
	{
		if (ptr[i] && ptr[i][0] && ptr[i][0] == c)
		{
			get_status(head, &ptr[i]);
			if (add_to_list(init, &ptr[i]))
				return (head->enomem = 1, rror(ENOMEM), NULL);
			sig = 1;
		}
		i++;
	}
	if (sig)
		return (init);
	free(init);
	return (NULL);
}

t_excmd	*init_excmd(void)
{
	t_excmd	*new;

	new = (t_excmd *)malloc(sizeof(t_excmd));
	if (!new)
		return (rror(ENOMEM), NULL);
	new->heredoc = 0;
	new->appen = 0;
	new->in_size = 0;
	new->out_size = 0;
	new->enomem = 0;
	new->cmd = NULL;
	new->in = NULL;
	new->out = NULL;
	return (new);
}

t_lcmd	*init_lcmd(size_t *i, _Bool *sig)
{
	t_lcmd	*new;

	new = (t_lcmd *)malloc(sizeof(t_lcmd));
	if (!new)
		return (rror(ENOMEM), NULL);
	new->data = NULL;
	new->prev = NULL;
	new->next = NULL;
	if (i)
		*i = 0;
	if (sig)
		*sig = 0;
	return (new);
}

t_lcmd	*undo_link(t_lcmd *ptr)
{
	t_lcmd	*keep;

	keep = ptr->next;
	if (ptr->next)
		ptr->next->prev = ptr->prev;
	ptr->prev->next = ptr->next;
	free(ptr->data);
	free(ptr);
	return (keep);
}

void	init_extract(size_t *size, size_t *i, int *wrk)
{
	*size = 0;
	*wrk = 0;
	*i = 0;
}
