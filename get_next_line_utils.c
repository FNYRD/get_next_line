/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jericard <jericard@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:31:58 by jericard          #+#    #+#             */
/*   Updated: 2025/11/26 18:32:00 by jericard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}


char	*ft_substr(char *s, size_t start, size_t len, size_t f)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	if (f)
		free (s);
	return (str);
}

ssize_t	ft_fb(char *s)
{
	ssize_t	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (*s != '\0' && *s != '\n')
	{
		i++;
		s++;
	}
	if (*s != '\n')
		return (-1);
	return (i);
}

char	*ft_strjoin(char *stash, char *buffer)
{
	char	*start;
	char	*str;

	if (!stash && !buffer)
		return (NULL);
	if (!stash)
		return (ft_strdup(buffer));
	str = (char *)malloc((ft_strlen(stash) + ft_strlen(buffer) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	start = str;
	while (*stash)
		*str++ = *stash++;
	while (*buffer)
		*str++ = *buffer++;
	*str = '\0';
	free(stash);
	return (start);
}
