/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:10:06 by nlorion           #+#    #+#             */
/*   Updated: 2023/04/22 13:08:07 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

char	*ft_strncpy(char *src, char *dst, int n)
{
	int	i;

	i = 0;
	if (!dst)
		return (0);
	if (n != 0)
	{
		while (src[i] != 0 && n > 0)
		{
			dst[i] = src[i];
			n--;
			i++;
		}
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_strcomp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
		return (1);
	return (0);
}

void	runnin(char *run, char **args, char **chenv)
{
	execve(run, args, chenv);
	free_matrix(args, get_matrix_2(args));
}

int	child_process(t_exec *exec, t_excmd *curr, char *run, char **args)
{
	run = get_path(exec, curr->cmd->data);
	if (!run)
		return (check_err(curr), 1);
	args = get_args(curr, curr->cmd);
	if (!(args))
		return (check_err(curr), 1);
	runnin(run, args, exec->chenv);
	return (0);
}

void	here_doc_msg(char *c, char *stream)
{
	write(1, "\n", 1);
	return_error("warning: ",
		"here-document at line 1 delimited by end-of-file (wanted `", 131);
	ft_putstr_fd(c + 2, 2);
	write(1, "')\n", 4);
	free(stream);
}
