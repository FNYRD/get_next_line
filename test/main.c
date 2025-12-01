#include "get_next_line.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	(void)argc;
	
	fd = open(argv[1], O_RDONLY);
	// (void)argv;
	// fd = 0;
	if (fd < 0)
		return (write(1, "error al abrir", ft_strlen("error al abrir")));
	line = get_next_line(fd);
	while (line)
	{
		printf("%s",line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	printf("\nEOF!");
	return (0);
}