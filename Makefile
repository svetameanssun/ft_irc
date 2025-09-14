NAME     = ircserv
TEST	 = test
CC       = c++
CFLAGS   = -Wall -Wextra -Werror -std=c++98
SRC_DIR  = src/
INC_DIR  = include/
OBJ_DIR  = obj/

INC_FILES =		Server.hpp \
				Client.hpp \
				Channel.hpp \
				MessageSender.hpp \
				CommandHandler.hpp \
				utils.hpp

INCLUDE  = $(addprefix $(INC_DIR), $(INC_FILES))

FILES    = 	main.cpp \
			Server.cpp \
			Client.cpp \
			Channel.cpp \
			MessageSender.cpp \
			CommandHandler.cpp \
			utils.cpp

SRCS     = $(addprefix $(SRC_DIR), $(FILES))
OBJS     = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRCS))


# Colores para mensajes en el Makefile
GREEN  = \033[0;32m
YELLOW = \033[0;33m
BLUE   = \033[0;34m
RED    = \033[0;31m
RESET  = \033[0m


all: $(OBJ_DIR) $(NAME) 

$(OBJ_DIR):
	@echo "$(GREEN) Creating obj folder... $(RESET)"
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS) $(INCLUDE)
	@$(CC) $(CFLAGS) -I $(INC_DIR) $(OBJS) -o $(NAME)
	@echo "$(GREEN) Compiled! $(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN) Objs removed $(RESET)"

fclean: clean
	@rm -f $(NAME)
	@if [ -n "$(TEST)" ]; then rm -rf $(TEST); fi
	@echo "$(GREEN) Removal completed :D $(RESET)"

re: fclean all

run: 
	@./$(NAME) 9000 9@atoi2025

test:
	@if [ ! -f "$(TEST)" ]; then \
    	$(CC) $(CFLAGS) -I $(INC_DIR) src/Channel.cpp src/Client.cpp src/Server.cpp \
									src/MessageSender.cpp src/CommandHandler.cpp src/utils.cpp test.cpp -o $(TEST); \
	fi
	@./$(TEST)

.PHONY: all clean fclean re run test