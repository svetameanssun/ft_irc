NAME     = ircserv
CC       = c++ #-g -fsanitize=address
CFLAGS   = -Wall -Wextra -Werror -std=c++98
SRC_DIR  = src/
INC_DIR  = include/
OBJ_DIR  = obj/

INC_FILES =		Server.hpp \
				Client.hpp \
				Channel.hpp \
				NetworkManager.hpp \
				ClientManager.hpp \
				ChannelManager.hpp \
				MessageSender.hpp \
				CommandHandler.hpp \
				AParserResult.hpp \
				CommandDispatcher.hpp \
				CommandParser.hpp \
				ParserResultJoin.hpp \
				ParserResultNick.hpp \
				ParserResultPass.hpp \
				ParserResultTopic.hpp \
				ParserResultInvite.hpp \
				ParserResultMode.hpp \
				ParserResultPrivmsg.hpp \
				ParserResultUser.hpp \
				ParserResultKick.hpp \
				ParserResultNotice.hpp \
				ParserResultPart.hpp \
				ParserResultQuit.hpp \
				ParserResultPing.hpp \
				Replies.hpp \
				utils.hpp \
				signals.hpp

INCLUDE  = $(addprefix $(INC_DIR), $(INC_FILES))

FILES    = 	main.cpp \
			Server.cpp \
			Client.cpp \
			Channel.cpp \
			ClientManager.cpp \
			ChannelManager.cpp \
			NetworkManager.cpp \
			MessageSender.cpp \
			CommandHandler.cpp \
			CmdPass.cpp \
			CmdJoin.cpp \
			CmdNick.cpp \
			CmdUser.cpp \
			CmdPrivmsg.cpp \
			CmdNotice.cpp \
			CmdPart.cpp \
			CmdQuit.cpp \
			CmdPingPong.cpp \
			CmdMode.cpp \
			CmdTopic.cpp \
			CmdKick.cpp \
			CmdInvite.cpp \
			AParserResult.cpp \
			CommandDispatcher.cpp \
			CommandDispatcherUtils.cpp \
			CommandParser.cpp \
			CommandParserUtils.cpp \
			ParserResultJoin.cpp \
			ParserResultNick.cpp \
			ParserResultPass.cpp \
			ParserResultTopic.cpp \
			ParserResultInvite.cpp \
			ParserResultMode.cpp \
			ParserResultPrivmsg.cpp \
			ParserResultUser.cpp \
			ParserResultKick.cpp \
			ParserResultNotice.cpp \
			ParserResultPart.cpp \
			ParserResultQuit.cpp \
			ParserResultPing.cpp \
			utils.cpp \
			signals.cpp

SRCS     = $(addprefix $(SRC_DIR), $(FILES))
SRCS_TEST = $(addprefix $(SRC_DIR), $(FILES_TEST))
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
	@$(CC) $(CFLAGS) -I $(INC_DIR) $(OBJS)  -o $(NAME)
	@echo "$(GREEN) Compiled! $(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN) Objs removed $(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN) Removal completed :D $(RESET)"

re: fclean all

run: 
	@./$(NAME) 6667 irc2026

valgrind:
	@valgrind --track-fds=yes ./$(NAME) 6667 irc2026

eval: 
	./ft_irc_eval/eval_ft_irc.sh > /tmp/irc_log.txt 2>&1
	@echo "$(GREEN) Evaluation completed! Check /tmp/irc_log.txt for results.

.PHONY: all clean fclean re run eval