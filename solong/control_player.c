#include "so_long.h"

static void	ft_move_player(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'E' && game->remaining_c == 0)
	{
		ft_printf_n("Number of movements: %n\n", game->movements + 1);
		ft_putstr_fd("Congratulations! Thank you for playing!\n", 1);
		ft_free_and_exit(game);
	}
	if (game->map [y][x] == 'C')
		game->map [y][x] = '0';
	game->x_axis = x;
	game->y_axis = y;
	game->movements++;
}

static int	ft_select_direction(int keycode, t_game *game)
{
	int	x;
	int	y;

	x = game->x_axis;
	y = game->y_axis;
	if (keycode == KEY_A)
		x--;
	else if (keycode == KEY_D)
		x++;
	else if (keycode == KEY_S)
		y++;
	else if (keycode == KEY_W)
		y--;
	if (game->map[y][x] == '1')
			return (-1);
	ft_move_player(game, x, y);
	ft_printf_n("Number of movements: %n\n", game->movements);
	return (0);
}

int	ft_control_player(int keycode, t_game *game)
{
	int	result;

	result = 1;
	if (keycode == KEY_ESC)
		ft_free_and_exit(game);
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
		result = ft_select_direction(keycode, game);
	if (result == 0)
	{
		game->remaining_c = 0;
		ft_place_images(game);
	}
	return (0);
}
