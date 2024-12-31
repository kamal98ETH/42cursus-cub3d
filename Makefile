MSDIR = mandatory/srcs/
BSDIR = bonus/srcs/
MODIR = mandatory/objs/
BODIR = bonus/objs/

LIBFT		= libft/libft.a

CC			= cc

TARGET		= cub3D
NAME		= .name
NAME_BONUS	= .bonus

FLAGS		= -Wall -Wextra -Werror -g3
MLXFLAGS	= -lmlx -lXext -lX11 -lm
# FLAGS	=	-fsanitize=address -g3

C_FILE		= main.c raycasting.c circle_halves.c rendering.c \
			parser.c fetch.c map.c split.c utils.c checks.c color.c texture.c \
			multi_split.c clean.c movement.c mov_utils.c hooks.c

BONUS_C_FILE = main_bonus.c raycasting_bonus.c circle_halves_bonus.c rendering_bonus.c door_bonus.c door_utils_bonus.c \
			minimap_bonus.c parser_bonus.c fetch_bonus.c map_bonus.c split_bonus.c utils_bonus.c checks_bonus.c color_bonus.c texture_bonus.c \
			multi_split_bonus.c clean_bonus.c movement_bonus.c mov_utils_bonus.c hooks_bonus.c death_bonus.c

SRCS		= $(addprefix $(MSDIR), $(C_FILE))
BONUS_SRCS	= $(addprefix $(BSDIR), $(BONUS_C_FILE))

OBJ			=	$(patsubst $(MSDIR)%.c, $(MODIR)%.o, $(SRCS))
OBJ_BONUS	=	$(patsubst $(BSDIR)%.c, $(BODIR)%.o, $(BONUS_SRCS))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
		@echo "\n"
		$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(TARGET) $(MLXFLAGS)
		@rm -rf $(NAME_BONUS)
		@touch $(NAME)

bonus: $(LIBFT) $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
		@echo "\n"
		$(CC) $(FLAGS) $(OBJ_BONUS) $(LIBFT) -o $(TARGET) $(MLXFLAGS)
		@rm -rf $(NAME)
		@touch $(NAME_BONUS)

$(MODIR)%.o: $(MSDIR)%.c
		@mkdir -p $(MODIR)
		$(CC) $(FLAGS) -c $< -o $@

$(BODIR)%.o: $(BSDIR)%.c
		@mkdir -p $(BODIR)
		$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
			$(MAKE) -C libft

clean:
		@rm -rf $(MODIR)
		@rm -rf $(BODIR)
		$(MAKE) -C libft clean

fclean: clean
		@rm -rf $(TARGET)
		@rm -rf $(NAME)
		@rm -rf $(NAME_BONUS)
		rm -f $(LIBFT)

re: fclean all

.SECONDARY: $(OBJ) $(OBJ_BONUS)

.PHONY : bonus all clean fclean re
