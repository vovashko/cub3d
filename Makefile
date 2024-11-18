CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = main.c
OBJS = $(SRCS:.c=.o)
NAME = cub3d
MLX_FLAGS = -framework OpenGL -framework IOkit -framework Cocoa 
MLX_LIB = MLX42/build/libmlx42.a

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(MLX_LIB) -lglfw -L"/opt/homebrew/Cellar/glfw/3.4/lib" -I"/opt/homebrew/Cellar/glfw/3.4/include"

$(MLX_LIB):
	cd MLX42 && cmake -B build && cmake --build build -j4

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re