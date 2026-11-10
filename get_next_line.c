#include "get_next_line.h"

char	*free_all(char *buffer, char **stash)
{
	free(buffer);
	free(*stash);
	*stash = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (ft_strchr(stash, '\n') == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_all(buffer, &stash));
		buffer[bytes_read] = '\0';
		if (bytes_read > 0)
		{
			stash = ft_strjoin(stash, buffer);
			if (!stash)
				return (free_all(buffer, &stash));
		}
	}
	free(buffer);
	if (!stash)
		return (NULL);
	return (stash);
}
