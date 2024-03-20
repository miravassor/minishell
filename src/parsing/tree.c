/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:21:16 by avassor           #+#    #+#             */
/*   Updated: 2023/04/22 10:23:47 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

t_trunk	*build_trunk(t_tkn *tkn)
{
	t_trunk	*trunk;

	trunk = (t_trunk *)malloc(sizeof(t_trunk));
	if (!trunk)
		return (rror(ENOMEM), NULL);
	trunk->an = NULL;
	trunk->leafs = NULL;
	trunk->tkn = tkn;
	trunk->size = 0;
	trunk->envp = NULL;
	return (trunk);
}

t_trunk	*build_tree(t_tkn *tkn, t_env *envp)
{
	t_trunk	*trunk;
	t_tkn	*ptr;
	t_node	*node;

	trunk = NULL;
	node = NULL;
	ptr = tkn;
	trunk = build_trunk(tkn);
	if (!trunk)
		return (NULL);
	trunk->an = tkn_analyzr(trunk->tkn);
	if (!trunk->an)
		return (free(trunk), NULL);
	while (ptr)
	{
		ptr = build_node(trunk, ptr);
		if (ptr && ptr->err)
			return (free(trunk->an), free(trunk), free(ptr), NULL);
	}
	if (trunk->an->pipe)
		pipe_placer(trunk, node);
	trunk->envp = envp;
	return (trunk);
}

void	get_redir_type(t_tkn_analysis *an, t_tkn *tkn)
{
	if (tkn->id == GREATR)
	{
		if (tkn->data[1] && tkn->data[1] == '>')
			an->appen_redir += 1;
		else
			an->out_redir += 1;
	}
	if (tkn->id == LESS)
	{
		if (tkn->data[1] && tkn->data[1] == '<')
			an->here_doc += 1;
		else
			an->in_redir += 1;
	}
}

t_tkn_analysis	*do_analyz(t_tkn *tkn, t_tkn_analysis *an)
{
	while (tkn)
	{
		if (tkn->id == GREATR || tkn->id == LESS)
		{
			an->redir = 1;
			get_redir_type(an, tkn);
		}
		else if (tkn->id == PIPE)
		{
			an->pipe = 1;
			an->pipes += 1;
		}
		tkn = tkn->next;
	}
	return (an);
}

t_tkn_analysis	*tkn_analyzr(t_tkn *tkn)
{
	t_tkn_analysis	*an;
	t_tkn			*ptr;

	ptr = tkn;
	an = (t_tkn_analysis *)malloc(sizeof(t_tkn_analysis));
	if (!an)
		return (rror(ENOMEM), NULL);
	an->redir = 0;
	an->pipe = 0;
	an->in_redir = 0;
	an->out_redir = 0;
	an->appen_redir = 0;
	an->here_doc = 0;
	an->pipes = 0;
	return (do_analyz(ptr, an));
}
