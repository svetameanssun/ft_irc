
TARGET = parcer
CXXFLAGS = -Wall -Werror -Wextra -std=c++98
CXX = g++
RM = rm -f

SRC = Parcer.cpp \
	ParcerUtils.cpp \
	main.cpp

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(TARGET)
re: fclean all

.PHONY: all clean fclean re
