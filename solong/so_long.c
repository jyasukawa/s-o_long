#include "so_long.h"

static int	ft_check_file_name(char *file_name)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (file_name[i] != '\0')
		i++;
	if (i < 5)
		return (-1);
	i--;
	if (file_name[i--] != 'r')
		return (-1);
	if (file_name[i--] != 'e')
		return (-1);
	if (file_name[i--] != 'b')
		return (-1);
	if (file_name[i--] != '.')
		return (-1);
	if (file_name[i] == '/' || file_name[i] == '.')
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		exit(1);
	if (ft_check_file_name(argv[1]) == -1)
	{
		ft_putstr_fd("Error\nThe file name is invalid.\n", 2);
		exit(1);
	}
	game = (t_game){0};
	ft_read_map(&game, argv[1]);
	ft_check_errors(&game);
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
		ft_free_and_exit(&game);
	game.win_ptr = mlx_new_window(game.mlx_ptr, (int)(game.map_width * 64), (int)(game.map_height * 64), "so_long");
	if (game.win_ptr == NULL)
		ft_free_and_exit(&game);
	ft_create_images(&game);
	ft_place_images(&game);
	mlx_hook(game.win_ptr, 2, 0, ft_control_player, &game);
	mlx_hook(game.win_ptr, 17, 0, ft_free_and_exit, &game);
	mlx_loop(game.mlx_ptr);
	exit(0);
}

// 今回マップの表示はXサーバを利用している。
// そんでもってXサーバを利用する上で便利なライブラリ(今後使うmlx系関数はここから)が事前に用意されている。
// 1. マップのソースを引数で受け取り、読み込む、(Xサーバの)windowで表示するためのマップ情報を用意する。
// 2. mlx系関数を使ってwindowに表示するための情報を用意する(各マスの画像の用意など)
// 3. マップを表示させる。

// mlx_init：全てをつかさどるポインタがとれる。
// Xサーバを利用するために必要な情報を持った構造体のポインタを返してくれる。
// mlx_new_window
// 使用するwindowの情報を持った構造体のポインタを返してくれる。
// mlx_xpm_file_to_image
// xpmファイル（今回だと事前に用意した各マスの画像）を元にimage情報を持った構造体のポインタを返してくれる。
// mlx_put_image_to_window
// window内の指定した位置にimageを表示してくれる。
// mlx_hook
// mlx_loop実行中に、red cross(xボタン)を押された際など特定のイベント発生時に実行する関数を指定できる。
// mlx_loop：ゲームのloop処理が始まる。
// 事前に指定した関数(例えば、マップを表示する関数)を実行するなどの、ループ処理をしてくれる。
// = プログラムが終了処理をするまで、マップを表示し続けてゲームを続行する。
// loopは事前に_hookした処理を繰り返す。
// ということで、hookを作るのがメインタスクだと悟る。

// mlx_loop_hook
// mlx_loop内で、実行する関数を指定できる。
// mlx_key_hook
// mlx_loop実行中に、keyを押された際に実行する関数を指定できる。