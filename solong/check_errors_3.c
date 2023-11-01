#include "so_long.h"

static void ft_free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

static int	ft_flood_check(char **map)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (map[j] != NULL)
	{
		i = 0;
		while (map[j][i] != '\0')
		{
			if (map[j][i] == 'C' || map[j][i] == 'E')
					return (-1);
			i++;
		}
		j++;
	}
	return (0);
}

static void	ft_flood_fill(char **map, t_point p)
{
	if (map[p.y][p.x] == '1' || map[p.y][p.x] == 'F')
		return ;
	map[p.y][p.x] = 'F';
	ft_flood_fill(map, (t_point){p.y - 1, p.x});
	ft_flood_fill(map, (t_point){p.y + 1, p.x});
	ft_flood_fill(map, (t_point){p.y, p.x - 1});
	ft_flood_fill(map, (t_point){p.y, p.x + 1});
}

static char **ft_clone_map(t_game *game)
{
	char					**clone;
	size_t				x;
	static size_t	y;

	clone = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	if (clone == NULL)
		ft_free_and_exit(game);
	while (y < game->map_height)
	{
		clone[y] = (char *)malloc(sizeof(char) * ft_strlen(game->map[y]) + 1);
		if (clone[y] == NULL)
		{
			ft_free_strs(clone);
			ft_free_and_exit(game);
		}
		x = 0;
		while (x <= game->map_width + 1)
		{
			clone[y][x] = game->map[y][x];
			x++;
		}
		y++;
	}
	clone[game->map_height] = NULL;
	return (clone);
}

int	ft_check_paths(t_game *game)
{
	char	**tmp;
	int		i;

	tmp = ft_clone_map(game);
	ft_flood_fill(tmp, game->player_pos);
	i = ft_flood_check(tmp);
	ft_free_strs(tmp);
	return (i);
}
