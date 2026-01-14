# ----------------------------------
# PROJECT NAME
# ----------------------------------
NAME = philo

# ----------------------------------
# COMPILATION AND FLAGS
# ----------------------------------
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -I ./

# ----------------------------------
# PATH
# ----------------------------------
SRC_DIR    = src
OBJ_DIR    = obj

# ----------------------------------
# COLORS
# ----------------------------------
RESET       = \033[0m
BLACK       = \033[0;30m
RED         = \033[0;31m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
MAGENTA     = \033[0;35m
CYAN        = \033[0;36m
WHITE       = \033[0;37m

# ----------------------------------
# SOURCES
# ----------------------------------
SRC = main.c \
	$(SRC_DIR)/verif_arg.c \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ----------------------------------
# RULES
# ----------------------------------

all: $(NAME) banner

banner :
	@echo "	  ▄▄▄▄▄▄           ▄▄                                            " 
	@echo " █▀██▀▀▀█▄ █▄       ██                      █▄                    " 
	@echo "   ██▄▄▄█▀ ██    ▀▀ ██ ▀▀                   ██          ▄         "
	@echo "   ██▀▀▀   ████▄ ██ ██ ██ ▄██▀█ ▄███▄ ████▄ ████▄ ▄█▀█▄ ████▄▄██▀█"
	@echo " ▄ ██      ██ ██ ██ ██ ██ ▀███▄ ██ ██ ██ ██ ██ ██ ██▄█▀ ██   ▀███▄"
	@echo " ▀██▀     ▄██ ██▄██▄██▄███▄▄██▀▄▀███▀▄████▀▄██ ██▄▀█▄▄▄▄█▀  █▄▄██▀"
	@echo "                                      ██                          "
	@echo "                                      ▀                           "
  
# Final link
$(NAME): $(OBJ)
	@echo "\033[1;34m[LINK] -> Creating $(NAME)...\033[0m"
	@$(CC) $(OBJ) -o $(NAME)
	@echo "\033[1;32m[OK] -> $(NAME) ready!\033[0m"

# Compilation of .c in .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "\033[1;33m[CC] -> $<\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@

# Create obj dir
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Clean
clean:
	@echo "\033[1;31m[CLEAN] -> Removing object files...\033[0m"
	@rm -rf $(OBJ_DIR)

# Full Clean
fclean: clean
	@echo "\033[1;31m[FCLEAN] -> Removing executable...\033[0m"
	@rm -f $(NAME)

# Rebuild
re: fclean all

# ----------------------------------
# PHONY
# ----------------------------------
.PHONY: all clean fclean re