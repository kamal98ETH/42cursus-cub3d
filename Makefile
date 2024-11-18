NAME = cub3D

MINILIBX = MiniLibX/libmlx_linux.a

LIBFT = libft/libft.a

COMPILER = cc

# FLAGS = -Wall -Wextra -Werror
FLAGS = -g
# FLAGS	=	-fsanitize=address -g3

SRCS = main.c raycasting.c circle_halves.c rendering.c minimap.c parser.c fetch.c map.c split.c utils.c checks.c texture.c multi_split.c 

OBJS = $(SRCS:.c=.o)

all: $(MINILIBX) $(LIBFT) $(NAME)

bonus: all

$(NAME): $(OBJS)
		@echo "\n" 
		$(COMPILER) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -L ./MiniLibX -lmlx -lXext -lX11 -lm

.c.o:
	$(COMPILER) $(FLAGS) -c $< -o $@

$(MINILIBX):
			$(MAKE) -C MiniLibX

$(LIBFT):
			$(MAKE) -C libft

clean:
		rm -f $(OBJS)
		$(MAKE) -C MiniLibX clean
		$(MAKE) -C libft clean

fclean: clean
		rm -f $(NAME)
		rm -f $(LIBFT)

re: fclean all

.SECONDARY: $(OBJS)