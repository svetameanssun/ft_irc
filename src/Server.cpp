#include "Server.hpp"

// Default constructor
Server::Server()
: _serverName("irc_server"), _listenFd(-1), _port(0), _password(""),
    _running(false), _cmdHandler(*this), _clientManager(), _channelManager() {}

// Parametrized constructor
Server::Server(int port, const std::string &password)
: _serverName("irc_server"), _listenFd(-1), _port(port), _password(password),
    _running(false), _cmdHandler(*this), _clientManager(), _channelManager() {}

// Destructor
Server::~Server()
{
    if (_listenFd != -1)
        ::close(_listenFd);

    //free all clients & channels
    _clientManager.freeResources();
    _channelManager.freeResources();
    log_msg("Hi I am the server, I am done here :)");
}

void Server::init(char *argv[])
{
    //Check for input - password and port number
    //And remove the password
    setPassword(argv[2]);
    log_debug("Password: %s", getPassword().c_str());

    setPort(atoi(argv[1]));
    log_debug("Server listening in port number: %d", getPort());
}

//setters
void Server::setPort(int port) { _port = port; }
void Server::setPassword(const std::string password) { _password = password; }

//getters
const std::string &Server::getServerName() const { return _serverName; }
int Server::getPort() const { return _port; }
const std::string &Server::getPassword() const { return _password; }


void Server::dispatchCommand(Client *client, const std::string &cmd) { _cmdHandler.execute(client, cmd, this->_parcingResult); }

int Server::launchParcing(std::string messageStr)
{
	// string OUTSIDE the functions.
	//std::string messageStr;


	//messageStr = "JOIN        sveta       :42  gggg  fff 			\r\n";
	//messageStr = "JOIN        chan1,chan2,chan3,chan4       11,22,33,11  ";
	//messageStr = "JOIN newChannel";
	//messageStr = "JOIN #newChannel";
	//messageStr = "JOIN #newChannel,&anotherChannel,#wonderfulChannel,&a,&b 1234,9999,0000";
	//messageStr = "JOIN #newChannel,&anotherChannel,#wonderfulChannel,&a,&b 1234,9999,0000,8,9,7,6,5,4";
	//messageStr = "Join newChan"; // does not start with & or #
	//messageStr = "Join &newChan"; // OK
	//messageStr = "NICK newNick";
	//messageStr = "NICK newNickname"; //  nickname no longer than 9 chars (?)
	//messageStr = "NICK 1392r"; //  nickname cannotstart with digit
	//messageStr = "user newNickname"; // not enough parameters
	//messageStr = "user newNickname  dddd dddd"; // wrong input
	//messageStr = "user newNickname  dddd:dddd"; // wrong input
	//messageStr = "USER n@ewNickname :Hello world"; // wrong input 
	//messageStr = "USeR $newNickname :My Full NAME 37R98YWEE409WRUSC[-fp;t9E";
	
	CommandParcer parcer(messageStr);
	if (!parcer.splitMessage())
	{
		std::cout << "THIS";
		return (ERR_WRONGINPUT);// CHECK what ERR_VARIANT I can apply here! 
	}
	
	int result = parcer.commandProccess();//
	if (!parcer.getCommandDispatcher().getParserResult())
		return (result);
	this->_parcingResult = parcer.getCommandDispatcher().getParserResult();
	return result;
}

//TODO: Remove the const char param and put the return message correctly
void Server::executeRoutine(Client *client, std::string &rawCommand, const char *cmd)
{
	(void) cmd;
	int ret = launchParcing(rawCommand);

    log_debug("return value is: %d", ret);

    if (isAllowed(ret))
    {
        dispatchCommand(client, this->_parcingResult->getCommand());
        deleteParserResult();
    }
    else
	{
		log_warning("Error case not yet implemented");
        //MessageSender::sendNumeric("irc_server", client, ret, "not yet implemented");
	}

}

void    Server::deleteParserResult() { delete _parcingResult; }
