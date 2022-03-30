# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jaberkro <jaberkro@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/03/29 16:11:58 by jaberkro      #+#    #+#                  #
#    Updated: 2022/03/30 14:34:16 by jaberkro      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = so_long	
INC = -I ./include
FLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft/
LIBFT = libft/libft.a

MLX_DIR = MlX42/
MLX = MLX42/libmlx42.a

SRC_DIR = src
BUILD_DIR = obj

SRC = src/main.c

OBJ = $(subst $(SRC_DIR), $(BUILD_DIR), $(SRC:.c=.o))

# COLORS
PINK	= \x1b[35m
BLUE	= \x1b[34m
YELLOW	= \x1b[33m
GREEN	= \x1b[32m
RED		= \x1b[31m
RESET	= \x1b[0m

all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	cp $(LIBFT) ./$(NAME)
	cp $(MLX) ./$(NAME)
	gcc $(FLAGS) $(OBJ) $(LIBFT) $(MLX) $(INC) -lglfw -L "/Users/Jaberkro/.brew/opt/glfw/lib/" -o $(NAME)
	@echo "$(RED)Done $(GREEN)COM$(YELLOW)PI$(BLUE)LING $(PINK)SO_LONG$(RESET) :)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	gcc $(FLAGS) $(INC) -c $^ -o $@

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(MLX_DIR)
	@echo "$(RED)Done $(GREEN)CLEANING$(YELLOW) SO_LONG$(PINK) :)$(RESET)"

fclean: clean
	rm -f $(NAME)
	@echo "$(RED)Done $(GREEN)FANCY CLEANING$(YELLOW) SO_LONG$(PINK) :)$(RESET)"

re: fclean all

.PHONY: all clean fclean re
