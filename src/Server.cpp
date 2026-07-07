/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** MyFtp BTTF
*/

#include "Server.hpp"

Server::Server(int port) : _port(port), _control_socket(_port) {
    addSocketToPoll(_control_socket);
}

void Server::addSocketToPoll(Socket obj) {
    struct pollfd newPollFd;
    newPollFd.fd = obj.getSocketFd();
    newPollFd.events = POLLIN | POLLPRI | POLLOUT;
    _pollArray.push_back(newPollFd);
}

void Server::doPoll() {
    poll(_pollArray.data(), _pollArray.size(), 5000);
}

void Server::acceptClient() {
    int newSocketFd;
    struct sockaddr_in newAdress;
    socklen_t newAdressSize;
    ClientSession newClient;
    struct pollfd newPollCase;

    newSocketFd = accept(_control_socket.getSocketFd(), (struct sockaddr *)&newAdress, &newAdressSize);
    newClient.controlFd = newSocketFd;
    _clientVector.push_back(newClient);
    newPollCase.fd = newSocketFd;
    newPollCase.revents = POLLIN | POLLOUT;
}

void Server::handleEvent() {
    for (auto client : _clientVector) {
        for (auto pollClient : _pollArray) {
            if (client.controlFd == pollClient.fd) {
                client.events = pollClient.events;
                switch (pollClient.events) {
                    case POLLIN :
                        //read data
                        continue;
                    case POLLOUT :
                        // Writing possible;
                        continue;
                    case POLLERR :
                        // Handl error
                        continue;
                    case POLLHUP :
                        // close the clientSession
                        continue;
                    default:
                        // if not found;
                        continue;
                }
            }
        }
    }
}

void Server::handleCommand() {
    char buffer[4096];
    ssize_t bytesRead = 0;

    for (auto client : _clientVector) {
        if (client.events == POLLIN) {
            bytesRead = read(client.controlFd, buffer, sizeof(buffer) - 1);
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0';
            }
            std::string line(buffer);
            std::istringstream iss(line);
            std::string cmd, args;
            iss >> cmd >> args;
            // search in unordered map for cmd
            FactoryCommands factory;
            auto command = factory.getCommand(cmd);
            command.execute(args);
        }
    }
}
