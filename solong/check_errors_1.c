#include "so_long.h"

static int	ft_check_walls(char **map, size_t height, size_t width)
{
	size_t	i;

	i = 0;
	while (i < width)
	{
		if (map[0][i] != '1' || map[height - 1][i] != '1')
			return (-1);
		i++;
	}
	i = 1;
	while (i < height - 1)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (-1);
		i++;
	}
	return (0);
}

static int	ft_check_map_shape(char **map, size_t map_width)
{
	size_t	width;
	size_t	x;
	size_t	y;

	width = map_width;
	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\n' && map[y][x])
			x++;
		if (x != width)
			return (-1);
		y++;
	}
	return (0);
}

static int	ft_count_width(char *str)
{
	size_t	x;

	x = 0;
	while (str[x] != '\0')
		x++;
	if (str[x - 1] == '\n')
		x--;
	return (x);
}

void	ft_check_errors(t_game *game)
{
	game->map_width = ft_count_width(game->map[0]);
	if (game->map_height > 15 || game->map_width > 26)
	{
		ft_putstr_fd("Error\nThe map size is too large.\n", 2);
		ft_free_and_exit(game);
	}
	if (ft_check_map_shape(game->map, game->map_width) == -1)
	{
		ft_putstr_fd("Error\nThe map is not a rectangle or contains empty lines.\n", 2);
		ft_free_and_exit(game);
	}
	if (ft_check_walls(game->map, game->map_height, game->map_width) == -1)
	{
		ft_putstr_fd("Error\nThe map is missing the walls.\n", 2);
		ft_free_and_exit(game);
	}
	ft_check_components(game);
	if (ft_check_paths(game) == -1)
	{
		ft_putstr_fd("Error\nThe map is unplayable.\n", 2);
		ft_free_and_exit(game);
	}
}
