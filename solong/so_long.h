#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>
# include "../minilibx/mlx.h"

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define YES -1
# define NO 1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

typedef struct s_point 
{
	size_t	y;
	size_t	x;
}	t_point;

typedef struct s_game
{
	int			fd;
	int			p_count;
	int			c_count;
	int			e_count;
	int			x_axis;
	int			y_axis;
	int			remaining_c;
	char		*buff_ptr;
	char		**map;
	void		*floor;
	void		*wall;
	void		*player;
	void		*exit;
	void		*collectible;
	void		*mlx_ptr;
	void		*win_ptr;
	size_t	map_height;
	size_t	map_width;
	size_t	movements;
	t_point	player_pos;

}	t_game;

void		ft_check_errors(t_game *game);
void		ft_check_components(t_game *game);
int			ft_check_paths(t_game *game);
int			ft_control_player(int keycode, t_game *game);
void		ft_create_images(t_game *game);
void		ft_place_images(t_game *game);
void		ft_read_map(t_game *game, char *map_file);
void		ft_putstr_fd(char *s, int fd);
int			ft_free_and_exit(t_game *game);

char		*get_next_line_n(int fd, t_game *game);
size_t	ft_strlen(char *s);
char		*ft_strchr_null(char *s, char c);
char		*ft_strjoin_free(char *buffer, char *tmp, int *is_error);
char		*ft_calloc_forone(size_t count, size_t size);
char		*ft_error_found(char *buffer, int *is_error);

void		ft_printf_n(const char *format, ...);

#endif
