/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jericard <jericard@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:31:44 by jericard          #+#    #+#             */
/*   Updated: 2025/11/26 18:31:45 by jericard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"get_next_line.h"

char    *get_next_line(int fd)
{
    static char *stash;
    char        *buffer;
    ssize_t     bytes;
    char        *line;

    // 1) Comprobar fd y BUFFER_SIZE
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes = 1;
	while (ft_fb(stash) == -1 && bytes > 0)
	{		
		// 2) Reservar buffer
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
		{
			if (stash)
				free (stash);
			return (NULL);
		}
		// 3) Leer del fd
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
		{		
			// 4) Tratar casos bytes < 0 (error)
			if (bytes < 0)
			{
				if (stash)
					free (stash);
				free (buffer);
				return (NULL);
			}
			// 4.5) Tratar casos bytes = 0 (EOF)
			if (bytes = 0)
			{
				free(buffer);
				if (stash)
				{
					buffer = stash;
					stash = NULL;
					return (buffer);
				}
				return (NULL);
			}
		}
		// 5) (Más adelante) acumular en stash, buscar '\n', etc.
		buffer[bytes] = '\0';
		// 6) Creacion de stash
		stash = ft_strjoin(stash, buffer);
		free(buffer);
	}
	line = ft_substr(stash, 0, ft_fb(stash) + 1, 0);
	stash = ft_substr(stash, ft_fb(stash) + 1, ft_strlen(stash), 1);
	return (line);
}
