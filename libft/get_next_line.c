/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:32:14 by bgretic           #+#    #+#             */
/*   Updated: 2024/09/11 16:59:09 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	get_line(char **stash, char **line, int *error)
{
	static int	index1 = 0;
	static int	index2 = 0;

	if (!*stash || !(*stash)[index2])
		return (free_that(stash));
	while ((*stash)[index1] && (*stash)[index1] != '\n')
		index1++;
	*line = (char *)ft_calloc((index1 - index2) + 2, sizeof(char));
	if (!*line)
		return (*error = 1, free_that(stash));
	ft_strlcpy(*line, &((*stash)[index2]), (index1 - index2) + 2);
	if ((*stash)[index1] == '\n')
		index1++;
	index2 = index1;
}

static int	fill_stash(char **stash, char *buffer, int readed_chars)
{
	*stash = ft_realloc(*stash, ft_strlen(*stash) + 1, (ft_strlen(*stash)
				+ readed_chars) + 1);
	if (!*stash)
		return (1);
	ft_strlcat(*stash, buffer, (ft_strlen(*stash) + readed_chars) + 1);
	return (0);
}

char	*get_next_line(int fd, int *error)
{
	static char	*stash = NULL;
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			readed_chars;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_that(&stash), NULL);
	line = NULL;
	readed_chars = 0;
	ft_bzero(buffer, BUFFER_SIZE + 1);
	while (1)
	{
		readed_chars = read(fd, buffer, BUFFER_SIZE);
		if (readed_chars == 0)
			break ;
		if (readed_chars == -1)
			return (*error = 1, free_that(&stash), NULL);
		if (fill_stash(&stash, buffer, readed_chars) == 1)
			return (*error = 1, NULL);
		ft_bzero(buffer, BUFFER_SIZE + 1);
		readed_chars = 0;
	}
	get_line(&stash, &line, error);
	return (line);
}
