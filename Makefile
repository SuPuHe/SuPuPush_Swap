# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/18 10:55:38 by omizin            #+#    #+#              #
#    Updated: 2025/04/30 13:00:56 by omizin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET_COLOR	= \033[0m			# Reset to default color
YELLOW		= \033[1;33m		# Brighter yellow
BLUE		= \033[1;34m		# Bright blue
GREEN		= \033[1;32m		# Bright green
RED			= \033[1;31m		# Bright red
CYAN		= \033[1;36m		# Bright cyan

NAME = push_swap
CHEKER_NAME = checker

SUPULIB_DIR = SuPuLib
SUPULIB_REPO = https://github.com/SuPuHe/SuPuLib.git
SRCS_DIR = srcs
OBJS_DIR = objs
INCS_DIR = includes

INCLUDE = -I$(INCS_DIR) -I$(SUPULIB_DIR)/libft/includes -I$(SUPULIB_DIR)/ft_printf/includes -I$(SUPULIB_DIR)/get_next_line/includes
CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDE)

RM = rm -rf

SRCS = swap_moves.c rotation_moves.c input_parsing.c helpers.c \
		sorting_helpers.c input_with_one_argc.c sorting.c calculating_sorting.c main_sorting.c \
		main_helpers.c

MAIN_PUSH = push_swap.c

CHEKER_SRCS = checker.c

SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
MAIN_PUSH := $(addprefix $(SRCS_DIR)/, $(MAIN_PUSH))
CHEKER_SRCS := $(addprefix $(SRCS_DIR)/, $(CHEKER_SRCS))

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
MAIN_PUSH_OBJS = $(MAIN_PUSH:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
CHEKER_OBJS = $(CHEKER_SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(SUPULIB_DIR)/SuPuLib.a $(NAME) $(CHEKER_NAME)

$(SUPULIB_DIR):
	@git clone $(SUPULIB_REPO) $(SUPULIB_DIR)
	@echo "$(GREEN)SuPuLib cloned successfully$(RESET_COLOR)"

$(SUPULIB_DIR)/SuPuLib.a: | $(SUPULIB_DIR)
	@$(MAKE) -C $(SUPULIB_DIR)

# Compile push_swap
$(NAME): $(SUPULIB_DIR)/SuPuLib.a $(OBJS) $(MAIN_PUSH_OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MAIN_PUSH_OBJS) $(SUPULIB_DIR)/SuPuLib.a -o $(NAME)
	@echo "$(GREEN)push_swap compiled successfully$(RESET_COLOR)"

$(CHEKER_NAME): $(SUPULIB_DIR)/SuPuLib.a $(CHEKER_OBJS) $(OBJS)
	@$(CC) $(CFLAGS) $(CHEKER_OBJS) $(OBJS) $(SUPULIB_DIR)/SuPuLib.a -o $(CHEKER_NAME)
	@echo "$(GREEN)cheker compiled successfully$(RESET_COLOR)"

# Compile object files
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

bonus: all

clean:
	@$(RM) $(OBJS_DIR)
	@$(MAKE) -C $(SUPULIB_DIR) clean
	@echo "$(GREEN)Clean sucessfully$(RESET_COLOR)"

fclean: clean
	@$(RM) $(NAME) $(CHEKER_NAME)
	@$(MAKE) -C $(SUPULIB_DIR) fclean
	@echo "$(GREEN)Fclean sucessfully$(RESET_COLOR)"

re: fclean all

.PHONY: all clean fclean re bonus
