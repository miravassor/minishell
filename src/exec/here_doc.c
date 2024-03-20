/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:54:29 by mira              #+#    #+#             */
/*   Updated: 2023/04/22 11:45:44 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

_Bool	go_and_read(t_exec *exec, t_excmd *curr)
{
	t_lcmd	*in;
	char	*c;

	in = curr->cmd;
	if (curr->in)
		in = curr->in;
	while (in)
	{
		c = in->data;
		if (c[0] && c[0] == '<' && c[1] && c[1] == '<')
			in->data = create_file_here(exec, c);
		if (!in->data)
		{
			if (curr->in)
			{
				free_link(curr->in);
				curr->in = NULL;
			}
			break ;
		}
		in = in->next;
	}
	return (0);
}

char	*create_file_here(t_exec *exec, char *c)
{
	char	*file;
	char	*plc;
	size_t	size;
	size_t	i;
	size_t	j;

	exec->hd += 1;
	plc = ft_itoa(exec->hd);
	size = ft_strlen(".hd_") + ft_strlen(plc);
	file = (char *)malloc(sizeof(char) * (size + 1));
	if (!file)
		return (NULL);
	file[0] = '.';
	file[1] = 'h';
	file[2] = 'd';
	file[3] = '_';
	i = 0;
	j = 4;
	while (plc[i])
		file[j++] = plc[i++];
	file[j] = '\0';
	free(plc);
	return (open_doc(exec, file, c));
}

void	hd_loop(char *c, int in, int dupl, t_exec *exec)
{
	char	*stream;

	stream = NULL;
	while (1)
	{
		write(1, "> ", 2);
		stream = get_next_line(0, c + 2);
		if (hd_quit(dupl, stream, c, exec) == 1)
			break ;
		write(in, stream, ft_strlen(stream));
		free(stream);
	}
	close(in);
	close(dupl);
}

char	*open_doc(t_exec *exec, char *file, char *c)
{
	int		in;
	int		dupl;

	g_status = 0;
	dupl = dup(STDIN_FILENO);
	in = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (in < 0)
	{
		close(in);
		return (NULL);
	}
	run_signals(4);
	hd_loop(c, in, dupl, exec);
	close(in);
	close(dupl);
	if (exec->hd_err == 1)
		return (free(file), NULL);
	return (update_redir(exec, file, c));
}

char	*update_redir(t_exec *exec, char *file, char *c)
{
	size_t	fsize;
	size_t	i;
	size_t	j;

	(void)exec;
	i = 1;
	free(c);
	c = NULL;
	fsize = ft_strlen(file) + 1;
	c = (char *)malloc(sizeof(char) * (fsize + 1));
	if (!c)
		return (NULL);
	c[0] = '<';
	j = 0;
	while (file[j])
		c[i++] = file[j++];
	c[i] = '\0';
	free(file);
	return (c);
}
