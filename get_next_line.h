/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jericard <jericard@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:32:11 by jericard          #+#    #+#             */
/*   Updated: 2025/11/26 18:32:12 by jericard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
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
