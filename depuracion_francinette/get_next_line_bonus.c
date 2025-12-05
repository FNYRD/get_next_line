/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jericard <jericard@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:48:12 by jericard          #+#    #+#             */
/*   Updated: 2025/12/03 14:48:14 by jericard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*zero(char **stash, char **buffer, ssize_t bytes)
{
	char	*line;

	if (buffer && *buffer)
	{
		free(*buffer);
	}
	if (bytes < 0)
	{
		if (*stash)
			free (*stash);
		*stash = NULL;
		return (NULL);
	}
	if (*stash && **stash != '\0')
	{
		line = *stash;
		*stash = NULL;
		return (line);
	}
	free(*stash);
	*stash = NULL;
	return (NULL);
}

static int	fd_fail(int fd, char **stash)
{
	char	dummy;

	if (read(fd, &dummy, 0) < 0)
	{
		if (stash && *stash)
		{
			free(*stash);
			*stash = NULL;
		}
		return (0);
	}
	return (1);
}

char	*null_cases(char *line, char **stash)
{
	if (!line || !*stash)
	{
		if (line)
			free (line);
		if (*stash)
			free (*stash);
		*stash = NULL;
		return (NULL);
	}
	return (line);
}

static char	*processor(int fd, ssize_t bytes, char	**stash)
{
	char	*buffer;
	char	*line;

	if (fd_fail(fd, stash) == 0)
		return (NULL);
	while (ft_fb(*stash) == -1 && bytes > 0)
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (zero(stash, NULL, -1));
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			return (zero(stash, &buffer, bytes));
		buffer[bytes] = '\0';
		*stash = ft_strjoin((*stash), buffer);
		free(buffer);
	}
	if (!*stash)
		return (NULL);
	line = ft_substr(*stash, 0, ft_fb(*stash) + 1, 0);
	*stash = ft_substr(*stash, ft_fb(*stash) + 1, \
flen(*stash), 1);
	return (null_cases(line, stash));
}

char	*get_next_line(int fd)
{
	static char	*mstash[MAX_FD];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	return (processor(fd, 1, &mstash[fd]));
}
