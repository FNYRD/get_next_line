#include	"gnl.h"

char    *zero(char **stash, char **buffer, ssize_t bytes)
{
	char *line;

    if (buffer && *buffer)
        free(*buffer);
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

char    *processor(int fd, ssize_t bytes, char	***mstash)
{
	char	    **stash;
	char		*buffer;
	char		*line;

    stash = &(*mstash)[fd];
	while (ft_fb((*stash)) == -1 && bytes > 0)
	{		
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (zero(stash, NULL, -1));
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			return (zero(stash, &buffer, bytes));
		buffer[bytes] = '\0';
		(*stash) = ft_strjoin((*stash), buffer);
		free(buffer);
	}
	if (!(*stash))
		return (NULL);
	line = ft_substr((*stash), 0, ft_fb((*stash)) + 1, 0);
	(*stash) = ft_substr((*stash), ft_fb((*stash)) + 1, ft_strlen((*stash)), 1);
	return (line);
}

char    *get_next_line(int fd)
{
    static char	**mstash;
    int i;

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