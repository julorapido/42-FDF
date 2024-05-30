NAME = fdf
GET_NEXT_LINE = get_next_line.c get_next_line_utils.c
SRCS_ = fdf.c utils.c window.c draw.c $(GET_NEXT_LINE)
SRCS_OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra

LIBFT_DIR = Libft/
LIBFT = $(LIBFT_DIR)/libft.a

UNAME =$(shell uname -s)
ifeq ($(shell uname -s), Linux)
	INCLUDES = -I/usr/include -Imlx -I$(LIBFT_DIR) -I./includes
else
	INCLUDES = -I/opt/X11/include -Imlx -I$(LIBFT_DIR)
endif
 
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a

ifeq ($(shell uname -s), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif
 
all: $(LIBFT) $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@echo "Making MiniLibX..."
	@make -C $(MLX_DIR)

$(LIBFT):
	@echo "Making Libft.."
	@make -C $(LIBFT_DIR)

$(NAME): $(SRCS_OBJ)
	gcc $(CFLAGS) $(SRCS_) $(INCLUDES) -lm -o $(NAME) $(SRCS_OBJ) $(LIBFT) \
		$(MLX_FLAGS)

clean:
	@echo "Removing .o files"
	rm -f $(SRCS_OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean all
