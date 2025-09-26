NAME  = ircparcer
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = AParcerResult.cpp \
	CommandDispatcher.cpp \
	CommandDispatcherUtils.cpp \
	CommandParcer.cpp \
	CommandParcerUtils.cpp \
	ParcerResultJoin.cpp \
	ParcerResultNick.cpp \
	ParcerResultPass.cpp \
	main.cpp

OBJS = $(SRC:.cpp=.o)

GREEN  = \033[0;32m
RESET  = \033[0m

all: $(NAME)

$(NAME): $(OBJS) 
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Compiled!$(RESET)"

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re


