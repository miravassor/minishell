/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:06:18 by nlorion           #+#    #+#             */
/*   Updated: 2023/01/27 12:31:38 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# define BUFFER_SIZE 2046

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include  "../libft.h"

char	*ft_check_line(char *line);

char	*ft_check_last_line(char *line, char *buf);

char	*get_next_line(int fd);

char	*ft_read_line(int fd, char *line, char *buf);

#endif
