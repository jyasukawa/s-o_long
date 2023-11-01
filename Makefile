CC					= cc
CFLAGS			= -Wall -Wextra -Werror

SOLONG			= $(addprefix solong/, control_player.c check_errors_1.c check_errors_2.c check_errors_3.c deploy_images.c read_map.c so_long.c so_long_utils.c get_next_line_n.c get_next_line_n_utils.c ft_printf_n.c)

SRCS				= $(SOLONG)
OBJS				= $(SRCS:.c=.o)
NAME				= so_long
MINILIBX		= minilibx
LIBRARY			= -L minilibx -lmlx -framework OpenGL -framework AppKit

all:					$(NAME)

$(NAME):			$(OBJS)
							make -C $(MINILIBX)
							$(CC) $(CFLAGS) $(SRCS) $(LIBRARY) -o $(NAME)

clean:
							make clean -C $(MINILIBX)
							rm -f $(OBJS)

fclean: 			clean
							rm -f $(NAME)

re: 					fclean all

.PHONY:				all clean fclean re

# -C オプションを使用して、make を別のディレクトリで実行できます。これは、サブディレクトリ内のプロジェクトをビルドする場合や、異なるディレクトリ内で make を実行する場合に便利です。
# 具体的には、make -C <ディレクトリ> という形式で使用します。-C オプションの後に指定されたディレクトリへ移動し、そのディレクトリ内の Makefile を読み込んでビルドプロセスを実行します。
# 例えば、以下のコマンドは my_project というサブディレクトリ内のプロジェクトをビルドするために -C オプションを使用しています
# make -C my_project
# これにより、make は my_project ディレクトリに移動し、そのディレクトリ内で定義された Makefile を使用してビルドプロセスを実行します。

# -L オプションは、コンパイラがライブラリの探索パスを指定するために使用されます。具体的には、ライブラリファイルを検索するディレクトリのパスを指定します。通常、このオプションは共有ライブラリ（ダイナミックリンクライブラリ）をリンクする際に使用されます。
# また、-L オプションをコンパイラに渡すだけで、ライブラリを実際にリンクするには -l オプションを使用することが一般的です。例えば、-lmylibrary と指定すると、libmylibrary.so（またはlibmylibrary.a）というライブラリをリンクします。