#include "so_long.h"

static void	ft_count_components(t_game *game, size_t y, size_t x)
{
	if (game->map[y][x] != '0' && game->map[y][x] != '1' && game->map[y][x] != 'C' && game->map[y][x] != 'E' && game->map[y][x] != 'P')
	{
		ft_putstr_fd("Error\nThere is invalid component in the map.\n", 2);
		ft_free_and_exit(game);
	}
	if (game->map[y][x] == 'C')
		game->c_count++;
	if (game->map[y][x] == 'E')
		game->e_count++;
	if (game->map[y][x] == 'P')
	{
		game->p_count++;
		game->player_pos.x = x;
		game->player_pos.y = y;
	}
}

void	ft_check_components(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 1;
	while (y < game->map_height - 1)
	{
		x = 1;
		while (x < game->map_width - 1)
		{
			ft_count_components(game, y, x);
			x++;
		}
		y++;
	}
	if (game->c_count == 0 || game->e_count != 1 || game->p_count != 1)
	{
		ft_putstr_fd("Error\nPlease check the number of each component.\n", 2);
		ft_free_and_exit(game);
	}
}
