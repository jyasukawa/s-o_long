#include "so_long.h"

static char	*ft_read_until(int fd, char *buffer, int *is_error)
{
	char		*tmp;
	ssize_t	bytes_read;

	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (tmp == NULL)
		return (ft_error_found(buffer, is_error));
	bytes_read = 1;
	while (ft_strchr_null(buffer, '\n') == NULL && bytes_read != 0)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(tmp);
			return (ft_error_found(buffer, is_error));
		}
		tmp[bytes_read] = '\0';
		buffer = ft_strjoin_free(buffer, tmp, is_error);
		if (buffer == NULL)
		{
			free(tmp);
			return (ft_error_found(buffer, is_error));
		}
	}
	free(tmp);
	return (buffer);
}

static char	*ft_clip_line(char *buffer, int *is_error)
{
	size_t	i;
	char		*str;

	if (buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (str == NULL)
		return (ft_error_found(buffer, is_error));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_save_remainder(char *buffer, int *is_error, char *nextline)
{
	size_t	i;
	size_t	j;
	char		*str;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i));
	if (str == NULL)
	{
		free(nextline);
		return (ft_error_found(buffer, is_error));
	}
	j = 0;
	while (buffer[++i])
		str[j++] = buffer[i];
	str[j] = '\0';
	free(buffer);
	return (str);
}

char	*get_next_line_n(int fd, t_game *game)
{
	static char	*buffer;
	char				*nextline;
	int					is_error;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	is_error = NO;
	buffer = ft_read_until(fd, buffer, &is_error);
	if (is_error == YES)
		ft_free_and_exit(game);
	nextline = ft_clip_line(buffer, &is_error);
	if (is_error == YES)
		ft_free_and_exit(game);
	buffer = ft_save_remainder(buffer, &is_error, nextline);
	if (is_error == YES)
		ft_free_and_exit(game);
	game->buff_ptr = buffer;
	return (nextline);
}
