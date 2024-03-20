/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:41:33 by mira              #+#    #+#             */
/*   Updated: 2023/04/22 12:59:17 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

int	g_status;

t_env	*term_ex(t_lxr *lxr, t_env *mini_env)
{
	if (lxr && lxr->env)
		mini_env = lxr->env;
	if (lxr)
		cleanr(NULL, NULL, lxr);
	return (mini_env);
}

t_lxr	*init_lxr(t_lxr *lxr)
{
	lxr = (t_lxr *)malloc(sizeof(t_lxr));
	if (!lxr)
		return (NULL);
	lxr->buff = NULL;
	lxr->data = NULL;
	lxr->size = 0;
	lxr->pos = -1;
	lxr->pos_data = -1;
	lxr->last_id = CHAR;
	lxr->prev_id = CHAR;
	lxr->env = NULL;
	return (lxr);
}

int	minishell(t_lxr *lxr, t_env *envp, char **arrenv)
{
	t_tkn	*tkn;
	t_trunk	*tree;

	tree = NULL;
	lxr->size = ft_strlen(lxr->buff);
	if (!lxr->size || chk_osp(lxr->buff) || buff_err(lxr->buff))
		return (2);
	skip_wspaces(lxr);
	tkn = tknize(lxr);
	if (!tkn)
		return (rror(ENOMEM), 1);
	tree = build_tree(tkn->next, envp);
	if (!tree)
		return (g_status = 2, cleanr(NULL, tkn, NULL), 2);
	if (syntaxr(tree->leafs, tree->envp))
		return (cleanr(tree, tkn, NULL), 2);
	if (interpretr(tree->leafs))
		return (g_status = 2, cleanr(tree, tkn, NULL), 2);
	execute(tree, tree->envp, arrenv);
	lxr->env = tree->envp;
	return (cleanr(tree, tkn, NULL), 0);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*mini_env;
	t_lxr	*lxr;
	char	*in;

	(void)ac;
	(void)av;
	in = NULL;
	lxr = NULL;
	mini_env = NULL;
	mini_env = build_env(envp);
	while (1)
	{
		sig_init();
		lxr = init_lxr(lxr);
		in = readline("$>Minishell ");
		if (!in)
			break ;
		add_history(in);
		lxr->buff = in;
		if (minishell(lxr, mini_env, envp) == 1)
			break ;
		mini_env = term_ex(lxr, mini_env);
	}
	return (good_bye(lxr, mini_env), EXIT_SUCCESS);
}
