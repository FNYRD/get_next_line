#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef MAX_FD
#  define MAX_FD 4096
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char    *get_next_line(int fd);
char	*ft_strjoin(char *stash, char *buffer);
char	*ft_substr(char *s, size_t start, size_t len, size_t f);

ssize_t	ft_fb(char *s);
size_t	ft_strlen(char *s);

# endif