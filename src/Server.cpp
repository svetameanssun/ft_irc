#include "Server.hpp"
//TODO: [RUBEN] Handle proper channel management for users when adding or removing them, it gives segfault in the Client manager
//TODO: [RUBEN] Check client and channel classes to find bugs
//TODO: [END] S I G N A L S
// Default constructor
Server::Server()
: _serverName("irc_server"), _listenFd(-1), _port(0), _password(""),
    _running(false), _cmdHandler(*this), _clientManager(), _channelManager(), _networkManager(6667) {}

// Parametrized constructor
Server::Server(int port, const std::string &password)
: _serverName("irc_server"), _listenFd(-1), _port(port), _password(password),
    _running(false), _cmdHandler(*this), _clientManager(), _channelManager(), _networkManager(port) {}

// Destructor
Server::~Server()
{
    if (_listenFd != -1)
        ::close(_listenFd);

    //free all clients & channels
	//TODO: [POINTERS] It seems that there is a problem with a double free here
    //_clientManager.freeResources();
    //_channelManager.freeResources();
    log_debug("[Server Destructor] Hi I am the server, I am done here :)");
}

void Server::init()
{
    log_debug("[Server] Password: %s", getPassword().c_str());
    log_debug("[Server] Server listening in port number: %d", getPort());
	log_debug("[Server] Running routine: ");
	run();
}

void Server::run() { _networkManager.run(*this); }

//setters
void Server::setPort(int port) { _port = port; }
void Server::setPassword(const std::string password) { _password = password; }

//getters
const std::string &Server::getServerName() const { return _serverName; }
int Server::getPort() const { return _port; }
const std::string &Server::getPassword() const { return _password; }

// command handling
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
	//TODO:[LANA] [POINTERS] I needed to do the CommandParcer dynamic, because the way it is implemented, it does not work at the memory level. 
	//TODO:[LANA] [POINTERS] We need to change the way the pointer of the parsed structure is delivered, because it is removed before arriving to the server structure
	CommandParcer *parcer = new CommandParcer(messageStr);
	if (!parcer->splitMessage())
	{
		std::cout << "THIS";
		return (ERR_WRONGINPUT);// CHECK what ERR_VARIANT I can apply here! 
	}

	int result = parcer->commandProccess();//
	if (!parcer->getCommandDispatcher().getParserResult())
		return (result);
	this->_parcingResult = parcer->getCommandDispatcher().getParserResult();

	return result;
}

void Server::executeRoutine(Client *client, std::string &rawCommand)
{
	int ret = launchParcing(rawCommand);

	//TODO: [LANA][QUIT command]: double check it
    log_debug("return value is: %d", ret);
	log_debug("Command in execute: %s", this->_parcingResult->getCommand().c_str());

    if (isAllowed(ret))
    {
		dispatchCommand(client, this->_parcingResult->getCommand());
		//TODO:[LANA] [POINTERS] We need to verify how to free the resources
        //deleteParserResult();
    }
    else
	{
		//TODO: I think we might need to do a func to answer based on the ret value
        MessageSender::sendNumeric("irc_server", client, ret, "command not supported");
	}
}

// communication with network layer

void Server::onClientConnected(int fd)
{
    Client *client = new Client(fd, "localhost"); // TODO: hostname later
    _clientManager.addClient(client);

    std::cout << "[Server] New client connected: fd=" << fd << std::endl;
}

void Server::onClientData(int fd)
{
    char buf[512];
    ssize_t bytes = recv(fd, buf, sizeof(buf), 0);

    if (bytes <= 0)
    {
        disconnectClient(fd, "Connection lost");
        return;
    }

    Client *client = _clientManager.findByFd(fd);
    if (!client)
	{
		log_warning("[onClientData] There is no client");
		return;
	}
	std::string raw(buf, bytes);
    client->appendToBuffer(std::string(buf, bytes));

    std::vector<std::string> messages = client->extractMessages();

	if (messages.size() == 0)
		log_warning("No messages");

    for (size_t i = 0; i < messages.size(); i++)
        executeRoutine(client, messages[i]);
}

void Server::disconnectClient(int fd, const std::string &reason)
{
    Client *client = _clientManager.findByFd(fd);

	if (!client) return;
	if (client->isRegistered())
    {
        std::string quitMsg = ":" + client->getPrefix() +
                              " QUIT :" + reason + "\r\n";

        _channelManager.broadcastToJoinedChannels(fd, quitMsg);
    }
	log_msg("User with fd=%d quitting IRC server", client->getFd());
    _networkManager.closeFd(fd);
	_channelManager.removeClientFromChannels(client);
    _clientManager.removeClient(fd);
}


void    Server::deleteParserResult() { delete _parcingResult; }
