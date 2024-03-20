/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:05:13 by mira              #+#    #+#             */
/*   Updated: 2023/04/22 13:14:19 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

t_exec	*exec_init(t_trunk *trk, t_env *envp, char **arrenv)
{
	t_exec	*exec;

	exec = trk->exec;
	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		return (rror(ENOMEM), NULL);
	exec->envp = envp;
	exec->chenv = arrenv;
	exec->path = split_path(envp);
	exec->pipes = trk->an->pipes;
	exec->pid = 0;
	exec->in = 0;
	exec->out = 1;
	exec->hd = 0;
	exec->hd_err = 0;
	if (exec->pipes)
	{
		exec->fd = malloc(sizeof(int *) * (exec->pipes * 2));
		if (!exec->fd)
			return (rror(ENOMEM), NULL);
	}
	else
		exec->fd = NULL;
	return (exec);
}

char	**split_path(t_env *envp)
{
	char	**env;
	t_env	*ptr;

	ptr = envp;
	while (ptr && ft_sprstrncmp(ptr->name, "PATH"))
		ptr = ptr->next;
	if (!ptr)
		return (NULL);
	env = ft_split(ptr->data, ':');
	return (env);
}

int	read_doc(char *cut)
{
	char	*stream;
	int		in;

	in = open(".tmpreadoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (in < 0)
		return (-1);
	while (1)
	{
		write(1, "> ", 2);
		stream = get_next_line(0, cut);
		if (!stream)
			break ;
		write(in, stream, ft_strlen(stream));
		free(stream);
	}
	run_signals(4);
	free(stream);
	close(in);
	in = open(".tmpreadoc", O_RDONLY);
	if (in < 0)
		return (-1);
	return (in);
}

size_t	get_matrix_2(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	is_redir(t_excmd *curr, int *fd)
{
	if (curr->appen || curr->heredoc || curr->in || curr->out)
	{
		if (file_opener(curr, fd))
			return (1);
	}
	return (0);
}
