NAME     = ircserv
CC       = c++
CFLAGS   = -Wall -Wextra -Werror -std=c++98
SRC_DIR  = src/
INC_DIR  = include/
OBJ_DIR  = obj/

INC_FILES =		Server.hpp \
				utils.hpp

INCLUDE  = $(addprefix $(INC_DIR), $(INC_FILES))

FILES    = 	main.cpp \
			Server.cpp \
			utils.cpp

SRCS     = $(addprefix $(SRC_DIR), $(FILES))
OBJS     = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRCS))


# Colores para mensajes en el Makefile
GREEN  = \033[0;32m
YELLOW = \033[0;33m
BLUE   = \033[0;34m
RED    = \033[0;31m
RESET  = \033[0m


all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	@$(CC) $(CFLAGS) -I $(INC_DIR) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Compiled! $(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@echo "$(GREEN) Creating obj folder... $(RESET)"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN) Objs removed $(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN) Removal completed :D $(RESET)"

re: fclean all

run: 
	@./$(NAME) 9000 9@atoi2025

.PHONY: all clean fclean re run