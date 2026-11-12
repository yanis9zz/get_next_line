/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutakh <yboutakh@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 19:08:38 by yboutakh          #+#    #+#             */
/*   Updated: 2026/11/12 19:08:41 by yboutakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	clean_stash(char **stash, size_t line_len)
{
	size_t	suffix_len;
	char	*new_stash;

	suffix_len = ft_strlen(*stash) - line_len;
	if (suffix_len == 0)
	{
		free(*stash);
		*stash = NULL;
		return (1);
	}
	new_stash = malloc(sizeof(char) * (suffix_len + 1));
	if (!new_stash)
		return (0);
	ft_memcpy(new_stash, *stash + line_len, suffix_len);
	new_stash[suffix_len] = '\0';
	free(*stash);
	*stash = new_stash;
	return (1);
}

static char	*extract_line(char **stash)
{
	size_t	line_len;
	char	*line;

	line_len = 0;
	while ((*stash)[line_len])
	{
		if ((*stash)[line_len] == '\n')
		{
			line_len++;
			break ;
		}
		line_len++;
	}
	line = malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, *stash, line_len);
	line[line_len] = '\0';
	if (!clean_stash(stash, line_len))
		return (free(line), NULL);
	return (line);
}

static char	*free_all(char *buffer, char **stash)
{
	free(buffer);
	free(*stash);
	*stash = NULL;
	return (NULL);
}

static int	read_until_newline(int fd, char **stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc((size_t)GNL_BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	bytes_read = 1;
	while (ft_strchr(*stash, '\n') == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, (size_t)GNL_BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_all(buffer, stash), 0);
		buffer[bytes_read] = '\0';
		if (bytes_read > 0)
		{
			*stash = ft_strjoin(*stash, buffer);
			if (!*stash)
				return (free_all(buffer, stash), 0);
		}
	}
	free(buffer);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_until_newline(fd, &stash))
		return (NULL);
	if (!stash)
		return (NULL);
	return (extract_line(&stash));
}

/*
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		write(1, line, ft_strlen(line));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
*/
