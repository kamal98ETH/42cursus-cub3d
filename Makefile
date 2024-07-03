NAME = cub3D

MINILIBX = MiniLibX/libmlx_linux.a

LIBFT = libft/libft.a

COMPILER = cc

# FLAGS = -Wall -Wextra -Werror
FLAGS = -g

SRCS = main.c

OBJS = $(SRCS:.c=.o)

all: $(MINILIBX) $(LIBFT) $(NAME)

bonus: all

$(NAME): $(OBJS)
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