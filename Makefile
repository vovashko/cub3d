CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = main.c init.c map_file_check.c controls.c drawing.c
SRCS_GNL = gnl/get_next_line.c gnl/get_next_line_utils.c
OBJS = $(SRCS:.c=.o) $(SRCS_GNL:.c=.o)
NAME = cub3d
MLX_FLAGS_MAC = -framework OpenGL -framework IOkit -framework Cocoa -lglfw -L"/opt/homebrew/Cellar/glfw/3.4/lib" -I"/opt/homebrew/Cellar/glfw/3.4/include"
MLX_LIB = MLX42/build/libmlx42.a
MLX_FLAGS_LINUX = -ldl -lglfw -pthread -lm

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
ifeq ($(shell uname), Darwin)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS_MAC) $(MLX_LIB)
else
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS_LINUX) $(MLX_LIB)
endif

$(MLX_LIB):
	cd MLX42 && cmake -B build && cmake --build build -j4

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re