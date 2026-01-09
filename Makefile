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
				NetworkManager.hpp \
				ClientManager.hpp \
				ChannelManager.hpp \
				MessageSender.hpp \
				CommandHandler.hpp \
				AParserResult.hpp \
				CommandDispatcher.hpp \
				CommandParcer.hpp \
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
				Replies.hpp \
				cmdtests.hpp \
				utils.hpp \

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
			CommandParcer.cpp \
			CommandParcerUtils.cpp \
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
			cmdtests.cpp \
			utils.cpp

FILES_TEST	=	Server.cpp \
				Client.cpp \
				Channel.cpp \
				ClientManager.cpp \
				ChannelManager.cpp \
				MessageSender.cpp \
				CommandHandler.cpp \
				CmdPass.cpp \
				AParserResult.cpp \
				CommandDispatcher.cpp \
				CommandDispatcherUtils.cpp \
				CommandParcer.cpp \
				CommandParcerUtils.cpp \
				ParserResultJoin.cpp \
				ParserResultNick.cpp \
				ParserResultPass.cpp \
				ParserResultTopic.cpp \
				ParserResultInvite.cpp \
				ParserResultMode.cpp \
				ParserResultPrivmsg.cpp \
				ParserResultUser.cpp \
				ParserResultKick.cpp \
				utils.cpp

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
	@if [ -n "$(TEST)" ]; then rm -rf $(TEST); fi
	@echo "$(GREEN) Removal completed :D $(RESET)"

re: fclean all

run: 
	@./$(NAME) 6667 irc2026

test:
	@if [ ! -f "$(TEST)" ]; then \
    	$(CC) $(CFLAGS) -I $(INC_DIR) $(SRCS_TEST) \
									cmdtests.cpp test.cpp -o $(TEST); \
	fi
	@./$(TEST)

.PHONY: all clean fclean re run test