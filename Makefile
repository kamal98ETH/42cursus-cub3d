NAME = cub3D

MINILIBX = MiniLibX/libmlx_linux.a

LIBFT = libft/libft.a

COMPILER = cc

# FLAGS = -Wall -Wextra -Werror
FLAGS = -g
# FLAGS	=	-fsanitize=address -g3

SRCS = main.c raycasting.c circle_halves.c rendering.c door.c door_utils.c minimap.c parser.c \
 fetch.c map.c split.c utils.c checks.c color.c texture.c multi_split.c clean.c movement.c mov_utils.c hooks.c death.c

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
		# $(MAKE) -C MiniLibX clean  		# uncomment to clean minilibx
		# $(MAKE) -C libft clean     		# uncomment to clean libft

fclean: clean
		rm -f $(NAME)
		# rm -f $(LIBFT) 			 		# uncomment to clean libft

re: fclean all

.SECONDARY: $(OBJS)