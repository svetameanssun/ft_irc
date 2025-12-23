#include "NetworkManager.hpp"
#include <iostream>

int main()
{
    NetworkManager net(6667);
    net.init();

    while (true)
    {
        net.pollOnce();

        const std::vector<pollfd>& fds = net.getPollFds();
        for (size_t i = 0; i < fds.size(); i++)
        {
            if (!(fds[i].revents & POLLIN))
                continue;

            if (fds[i].fd == fds[0].fd)
            {
                int clientFd = net.acceptClient();
                std::cout << "New client: " << clientFd << std::endl;
            }
            else
            {
                std::string data;
                ssize_t bytes = net.receiveFrom(fds[i].fd, data);

                if (bytes <= 0)
                {
                    std::cout << "Client disconnected\n";
                    net.closeFd(fds[i].fd);
                }
                else
                {
                    std::cout << "[RAW] " << data << std::endl;
                    net.sendTo(fds[i].fd, "ACK\r\n");
                }
            }
        }
    }
}
