NAME  = ircparcer
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRC_DIR = src/
INC_DIR = include/
OBJ_DIR = obj/

INC_FILES =	AParcerResult.hpp \
	CommandDispatcher.hpp \
	CommandParcer.hpp \
	ParcerResultJoin.hpp \
	ParcerResultNick.hpp \
	ParcerResultPass.hpp \
	ParcerResultUser.hpp \
	Replies.hpp

INCLUDE  = $(addprefix $(INC_DIR), $(INC_FILES))

SRC_FILES = AParcerResult.cpp \
	CommandDispatcher.cpp \
	CommandDispatcherUtils.cpp \
	CommandParcer.cpp \
	CommandParcerUtils.cpp \
	ParcerResultJoin.cpp \
	ParcerResultNick.cpp \
	ParcerResultPass.cpp \
	ParcerResultUser.cpp \
	main.cpp

SRCS     = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS     = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRCS))

# Colores para mensajes en el Makefile
GREEN  = \033[0;32m
YELLOW = \033[0;33m
BLUE   = \033[0;34m
RED    = \033[0;31m
RESET  = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	@$(CXX) $(CXXFLAGS) -I $(INC_DIR) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Compiled! $(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@echo "$(GREEN) Creating obj folder... $(RESET)"
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN) Objs removed $(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN) Removal completed :D $(RESET)"

re: fclean all

run: 
	@./$(NAME) 9000 9@ft_irc2025

.PHONY: all clean fclean re run
