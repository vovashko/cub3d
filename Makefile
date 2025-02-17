CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = main.c init.c utils.c hooks/controls.c \
	raycasting/raycaster.c  raycasting/drawing.c\
	parsing/colors.c parsing/parser_grow_map.c parsing/parser.c  parsing/parser_utils.c \
	validation/validate_map.c validation/validate_map_rows.c \
	validation/validator_utils.c validation/validator.c 
SRCS_GNL = gnl/get_next_line.c gnl/get_next_line_utils.c
OBJS = $(SRCS:.c=.o) $(SRCS_GNL:.c=.o)
NAME = cub3D
MLX_FLAGS_MAC = -framework OpenGL -framework IOkit -framework Cocoa -lglfw -L"/opt/homebrew/Cellar/glfw/3.4/lib" -I"/opt/homebrew/Cellar/glfw/3.4/include"
MLX_LIB = MLX42/build/libmlx42.a
MLX_FLAGS_LINUX = -ldl -lglfw -pthread -lm
LIBFT = libft/libft/libft.a


all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT)
ifeq ($(shell uname), Darwin)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS_MAC) $(MLX_LIB) $(LIBFT)
else
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS_LINUX) $(MLX_LIB) $(LIBFT)
endif

$(MLX_LIB):
	cd MLX42 && cmake -B build && cmake --build build -j4

$(LIBFT):
	cd libft/libft && make

clean:
	rm -f $(OBJS)
	cd libft/libft && make clean

fclean: clean
	rm -f $(NAME)
	cd libft/libft && make fclean

re: fclean all

.PHONY: all clean fclean re