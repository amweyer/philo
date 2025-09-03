# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amweyer <amweyer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/29 15:01:22 by amweyer           #+#    #+#              #
#    Updated: 2025/09/02 16:27:26 by amweyer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Sources
SRC =  $(SRC_DIR)/main.c \
#        $(SRC_DIR)/parsing.c \
#        $(SRC_DIR)/free.c \
#        $(SRC_DIR)/pipe.c \
#        $(SRC_DIR)/pipe_utils.c \
#        $(SRC_DIR)/pipe_init.c \
#        $(SRC_DIR)/get_next_line_utils_bonus.c \
#        $(SRC_DIR)/get_next_line_bonus.c

# Objects
OBJS := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compiler
CC = cc
CFLAGS = -Wall -Werror -Wextra
CPPFLAGS = -I $(INC_DIR) 

# Commands
RM = rm -f

# Colors
DEF_COLOR = \033[0;39m
GREEN = \033[0;92m

# Default target
all: $(NAME)

# Build executable
$(NAME): $(OBJS) | $(LIBFT_DIR)/libft.a $(PRINTF_DIR)/libftprintf.a
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)Compilation of $(NAME) done.$(DEF_COLOR)"

# Build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Create object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Ensure libraries are built
$(LIBFT_DIR)/libft.a:
	@$(MAKE) -C $(LIBFT_DIR) --silent

$(PRINTF_DIR)/libftprintf.a:
	@$(MAKE) -C $(PRINTF_DIR) --silent

# Clean object files
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --silent
	@$(MAKE) -C $(PRINTF_DIR) clean --silent
	@$(RM) $(OBJS)
	@echo "$(GREEN)Files clean up done.$(DEF_COLOR)"

# Full clean
fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent
	@$(MAKE) -C $(PRINTF_DIR) fclean --silent
	@$(RM) $(NAME)
	@echo "$(GREEN)Clean up done.$(DEF_COLOR)"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
