#include "so_long.h"

void	ft_create_images(t_game *game)
{
	int	x;
	int	y;

	game->floor = mlx_xpm_file_to_image(game->mlx_ptr, "textures/empty_space.xpm", &x, &y);
	game->wall = mlx_xpm_file_to_image(game->mlx_ptr, "textures/wall.xpm", &x, &y);
	game->collectible = mlx_xpm_file_to_image(game->mlx_ptr, "textures/collectible.xpm", &x, &y);
	game->exit = mlx_xpm_file_to_image(game->mlx_ptr, "textures/map_exit.xpm", &x, &y);
	game->player = mlx_xpm_file_to_image(game->mlx_ptr, "textures/player.xpm", &x, &y);
	if (!game->floor || !game->wall || !game->collectible || !game->exit || !game->player)
	{
		ft_putstr_fd("Error\nFailed to create the image.\n", 2);
		ft_free_and_exit(game);
	}
}

static void ft_store_initial_axis(t_game *game, size_t x, size_t y)
{
	game->x_axis = (int)x;
	game->y_axis = (int)y;
	game->map[y][x] = '0';
}

static void	ft_place_collectable(t_game *game, size_t x, size_t y)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->floor, (int)x * 64,(int) y * 64);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->collectible, (int)x * 64, (int)y * 64);
	game->remaining_c++;
}

void	ft_place_images(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->wall, (int)x * 64, (int)y * 64);
			if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->exit, (int)x * 64, (int)y * 64);
			if (game->map[y][x] == 'C')
				ft_place_collectable(game, x, y);
			if (game->map[y][x] == 'P')
				ft_store_initial_axis(game, x, y);
			if (game->map[y][x] == '0')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->floor, (int)x * 64, (int)y * 64);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->player, game->x_axis * 64, game->y_axis * 64);
}
