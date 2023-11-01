#include "so_long.h"

static void	ft_add_line(t_game *game, char *nextline)
{
	char		**tmp;
	size_t	y;

	game->map_height++;
	tmp = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	if (tmp == NULL)
	{
		free(game->buff_ptr);
		free(nextline);
		ft_free_and_exit(game);
	}
	y = 0;
	while (y < game->map_height - 1)
	{
		tmp[y] = game->map[y];
		y++;
	}
	tmp[y] = nextline;
	tmp[game->map_height] = NULL;
	if (game->map != NULL)
		free(game->map);
	game->map = tmp;
}

void	ft_read_map(t_game *game, char *map_file)
{
	char	*nextline;

	game->fd = open(map_file, O_RDONLY);
	if (game->fd == -1)
	{
		ft_putstr_fd("Error\nFailed to open the file.\n", 2);
		exit(1);
	}
	while (1)
	{
		nextline = get_next_line_n(game->fd, game);
		if (nextline == NULL)
			break;
		ft_add_line(game, nextline);
	}
	close(game->fd);
	if (game->map == NULL)
	{
		ft_putstr_fd("Error\nThe Map is empty.\n", 2);
		ft_free_and_exit(game);
	}
}
