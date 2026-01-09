#include "Server.hpp"
//TODO: [RUBEN] Handle proper channel management for users when adding or removing them, it gives segfault in the Client manager
//TODO [RUBEN] Check client and channel classes to find bugs
//TODO: Change the default constructor, it should always have a specified port
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
    log_msg("Hi I am the server, I am done here :)");
}

void Server::init(char *argv[])
{
    //TODO:: heck for input - password and port number
    //And remove the password
    setPassword(argv[2]);
    log_debug("[Server] Password: %s", getPassword().c_str());

    setPort(atoi(argv[1]));
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

//TODO: put the return message correctly
void Server::executeRoutine(Client *client, std::string &rawCommand)
{
	int ret = launchParcing(rawCommand);

	//TODO: [LANA][QUIT command]: apparently it segfaults somewhere; I've commented my code and it is not there
	//TODO: [LANA][PING command]: I do not see the PING command, is it mandatory or not really?
    log_debug("return value is: %d", ret);
	log_debug("Command in execute: %s", this->_parcingResult->getCommand().c_str());

    if (isAllowed(ret))
    {
		dispatchCommand(client, this->_parcingResult->getCommand());
		//TODO:[POINTERS] We need to verify how to free the resources
        //deleteParserResult();
		//TODO: Remove this at the end of the project
		std::cout << "<<==== Routine executed successfully =====>>" << std::endl;

    }
    else
	{
		log_warning("Wrong command. Error case not yet implemented. Return proper message");
        //MessageSender::sendNumeric("irc_server", client, ret, "not yet implemented");
	}
}

// communication with network layer

void Server::onClientConnected(int fd)
{
    Client *client = new Client(fd, "localhost"); // TODO: hostname later
    _clientManager.addClient(client);

    std::cout << "[Server] New client connected: fd=" << fd << std::endl;
}

//TODO: The recv func should be in the network layer I believe
//TODO: Remove all the log messages once the bug is fixed
void Server::onClientData(int fd)
{
    char buf[512];
    ssize_t bytes = recv(fd, buf, sizeof(buf), 0);

    if (bytes <= 0)
    {
        disconnectClient(fd);
        return;
    }

    Client *client = _clientManager.findByFd(fd);
    if (!client)
	{
		log_warning("[onClientData] There is no client");
		return;
	}
	log_debug("recv() returned %zd bytes", bytes);
	std::string raw(buf, bytes);
	log_debug("Raw data: [%s]", raw.c_str());
    client->appendToBuffer(std::string(buf, bytes));

	log_debug("Buffer of client: %s", client->getBuffer().c_str());
    std::vector<std::string> messages = client->extractMessages();

	if (messages.size() == 0)
		log_warning("No messages");
    for (size_t i = 0; i < messages.size(); i++)
	{
		log_debug("Executing routine...");
        executeRoutine(client, messages[i]);
	}
}

void Server::disconnectClient(int fd)
{
    Client *client = _clientManager.findByFd(fd);

    if (client)
	{
		log_debug("[Disconnect client]: bye bye baby");
	}
		//TODO: I guess it is just to send a message to the client
        //_commandHandler.handleQuit(client, "Connection closed");

    _networkManager.closeFd(fd);
    _clientManager.removeClient(fd);
}


void    Server::deleteParserResult() { delete _parcingResult; }
