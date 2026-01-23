#include "Server.hpp"

// Default constructor
Server::Server()
: _serverName("irc_server"), _port(0), _password(""),
    _running(false), _cmdHandler(*this), _clientManager(), _channelManager(), _networkManager(6667) { _cmdParser = NULL;/* <--- [LANA EDIT]*/}

// Parametrized constructor
Server::Server(int port, const std::string &password)
: _serverName("irc_server"), _port(port), _password(password),
    _running(false), _cmdHandler(*this), _clientManager(), _channelManager(), _networkManager(port) { _cmdParser = NULL; /* <--- [LANA EDIT]*/}

// Destructor
Server::~Server()
{
	if (this->_cmdParser)
		delete(this->_cmdParser); // <--- [LANA EDIT]
    log_msg("[Server] closing...");
}

//[LANA EDIT] ==============================================
CommandParser *Server::getCmdParser() { return _cmdParser; }

void Server::createCmdParser(std::string rawStr)
{
	if (this->_cmdParser){
    	delete(this->_cmdParser);
	}
	this->_cmdParser = new CommandParser(rawStr);
}
///=========================================================

void Server::init()
{
	// signal handling
	std::signal(SIGINT, signalHandler);
    //-----------------------------------
	//TODO: [END] remove the debug messages
    log_debug("[Server] Password: %s", getPassword().c_str());
    log_debug("[Server] Server listening in port number: %d", getPort());
	log_debug("[Server] Running routine: ");
	run();
}

void Server::run() { _networkManager.run(*this); }

void Server::stop()
{
	_running = false;
	std::vector<struct pollfd> fdVec = _networkManager.getPollFds();
	for (size_t i = 0; i < fdVec.size(); i++)
	{
		disconnectClient(fdVec[i].fd, "connection closed");
	}
}

//setters
void Server::setPort(int port) { _port = port; }
void Server::setPassword(const std::string password) { _password = password; }

//getters
const std::string &Server::getServerName() const { return _serverName; }
int Server::getPort() const { return _port; }
const std::string &Server::getPassword() const { return _password; }

// command handling
void Server::dispatchCommand(Client *client, const std::string &cmd) { _cmdHandler.execute(client, cmd, this->_parsingResult); }

int Server::launchParsing()
{
	// string OUTSIDE the functions.
	//std::string messageStr;
	//messageStr = "USeR $newNickname :My Full NAME 37R98YWEE409WRUSC[-fp;t9E";
	if (!_cmdParser->splitMessage())
	{
		std::cout << "THIS";
		return (ERR_WRONGINPUT);// CHECK what ERR_VARIANT I can apply here! 
	}

	int result = _cmdParser->commandProccess();//
	//if (!_cmdParser->getCommandDispatcher().getParserResult())
	if (result != 0){
		return (result);
	}
	//TODO: [POINTERS] Check this with Lana, important for free properly
	this->_parsingResult = _cmdParser->getCommandDispatcher().getParserResult();
	return result;
}

void Server::executeRoutine(Client *client, std::string &rawCommand)
{
	//CommandParser parser(rawCommand); // <--THIS WILL NOT WORK! we need OTHER solution! 
	this->createCmdParser(rawCommand); // We initiate _cmdParser of the Client class with the rawCommand in it
	
	int ret = launchParsing(); // we use launchParsing of the Server to parse the command client received.
	//if (ret != 0 || !_parsingResult)
	//{
    //	log_warning("Parsing failed");
    //	return;
	//}
	//TODO: I've changed this to check something
	//if (this->_cmdParser->flagMal)
	if(!_parsingResult)
	{
		log_warning("Parsing failed");
		return;
	}


	//TODO: [LANA][QUIT command]: double check it
    log_debug("return value is: %d", ret);
	if (_parsingResult)
		log_debug("Command in execute: %s", this->_parsingResult->getCommand().c_str());

    if (isAllowed(ret) && _parsingResult)
		dispatchCommand(client, this->_parsingResult->getCommand());
    else
	{
		//TODO: [RUBEN] I think we might need to do a func to answer based on the ret value
        MessageSender::sendNumeric("irc_server", client, ret, "command not supported");
	}

	//TODO: [POINTERS] We still do not handle properly pointers
	//if (_parsingResult)
	//	deleteParserResult();

}

// communication with network layer
void Server::onClientConnected(int fd)
{
	// TODO: [END] hostname (necessary?)
    Client *client = new Client(fd, "localhost"); 
    _clientManager.addClient(client);

    log_msg("[Server] New client connected: fd=%d,", fd);
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
	log_debug("Buffer: %s", client->getBuffer().c_str());
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

void    Server::deleteParserResult() { delete _parsingResult; }
