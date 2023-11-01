#include "so_long.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (s == NULL)
		return ;
  i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_free_and_exit(t_game *game)
{
	size_t	i;

	if (game->win_ptr != NULL)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free(game->mlx_ptr);
	i = 0;
	if (game->map != NULL)
	{
		while (game->map[i] != NULL)
			free(game->map[i++]);
	}
	free(game->map);
	exit (1);
	return (0);
}
