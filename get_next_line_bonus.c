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
		{
			free (*stash);
			*stash = NULL;
		}
		return (NULL);
	}
	if (*stash)
	{
		line = *stash;
		*stash = NULL;
		return (line);
	}
	return (NULL);
}

static int	fd_fail(int fd, char ***mstash)
{
	char	dummy;

	if (read(fd, &dummy, 0) < 0)
	{
		if (mstash && (*mstash)[fd])
		{
			free((*mstash)[fd]);
			(*mstash)[fd] = NULL;
		}
		return (0);
	}
	return (1);
}

static char	*processor(int fd, ssize_t bytes, char	***mstash)
{
	char	*buffer;
	char	*line;

	if (fd_fail(fd, mstash) == 0)
		return (NULL);
	while (ft_fb(((*mstash)[fd])) == -1 && bytes > 0)
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (zero(&(*mstash)[fd], NULL, -1));
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			return (zero(&(*mstash)[fd], &buffer, bytes));
		buffer[bytes] = '\0';
		(*mstash)[fd] = ft_strjoin(((*mstash)[fd]), buffer);
		free(buffer);
	}
	if (!(*mstash)[fd])
		return (NULL);
	line = ft_substr((*mstash)[fd], 0, ft_fb((*mstash)[fd]) + 1, 0);
	(*mstash)[fd] = ft_substr((*mstash)[fd], ft_fb((*mstash)[fd]) + 1, \
ft_strlen((*mstash)[fd]), 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	**mstash;
	int			i;

	i = -1;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	if (!mstash)
	{
		mstash = malloc(MAX_FD * sizeof(char *));
		if (!mstash)
			return (NULL);
		while (++i < MAX_FD)
			mstash[i] = NULL;
	}
	return (processor(fd, 1, &mstash));
}
