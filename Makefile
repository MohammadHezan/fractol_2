# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/11 16:32:01 by mhaizan           #+#    #+#              #
#    Updated: 2026/02/06 14:10:00 by mhaizan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Final executable name.
NAME = fractol
# C compiler used for all build steps.
CC = cc
# Mandatory warning flags for 42 projects + include path for local headers.
CFLAGS = -Wall -Wextra -Werror -Isrcs

# Project source files.
SRCS = 	srcs/main.c \
		srcs/init.c \
		srcs/event.c \
		srcs/rendering.c \
		srcs/maths.c \
		srcs/colors.c 

# Object files generated from source files.
OBJS = $(SRCS:.c=.o)

# MiniLibX source directory and produced static library.
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
# Link flags required by MiniLibX on Linux/X11.
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -I$(MLX_DIR)

# Generic compilation rule: compile one .c source into one .o object.
%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -O3 -c $< -o $@
	
# Default target: ensure MLX is built, then build project binary.
all: $(MLX_LIB) $(NAME)

# Build MiniLibX static library inside its own directory.
$(MLX_LIB): $(MLX_DIR)
	@make -C $(MLX_DIR)

# Clone MiniLibX dependency if it is not already present locally.
$(MLX_DIR):
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)

# Link all objects with MLX/X11 libraries to create final executable.
$(NAME): $(OBJS) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

# Remove compiled object files.
clean:
	rm -f $(OBJS)
	@make -C $(MLX_DIR) clean

# Remove object files and executable.
fclean: clean
	rm -f $(NAME)

# Rebuild project from a clean state.
re: fclean all

# Mark utility targets as phony (not real files).
.PHONY: all clean fclean re
