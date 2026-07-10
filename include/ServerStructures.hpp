/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** MyFtp
*/

#ifndef SERVERSTRUCTURES_HPP
    #define SERVERSTRUCTURES_HPP
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <arpa/inet.h>
    #include <poll.h>
    #include <vector>
    #include <string>
    #include "Socket.hpp"

enum Mode {
    NONE,
    ACTIVE,
    PASSIVE
};

struct DataChannel {
    Mode mode;
    int listenFd;
    int DataFd;
    sockaddr_in peerAddr;

    DataChannel() : mode(NONE), listenFd(-1), DataFd(-1), peerAddr{} {}
};

struct ClientSession {
    int controlFd;
    bool loggedIn;
    std::string username;
    std::string cwd;
    DataChannel data;
    std::string inputBuffer;
    std::string responseBuffer;
    short events;
    int serverPort;

    ClientSession() : controlFd(-1), loggedIn(false), username(""), cwd("/"), data(), inputBuffer("") {}
};

static bool openDataConnection(ClientSession& client)
{
    if (client.data.mode == PASSIVE) {
        int dataFd = accept(client.data.listenFd, nullptr, nullptr);
        if (dataFd < 0)
            return false;
        close(client.data.listenFd);
        client.data.listenFd = -1;
        client.data.DataFd = dataFd;
        return true;
    }

    if (client.data.mode == ACTIVE) {
        int dataFd = socket(AF_INET, SOCK_STREAM, 0);
        if (dataFd < 0)
            return false;
        if (connect(dataFd,
                    (sockaddr*)&client.data.peerAddr,
                    sizeof(client.data.peerAddr)) < 0) {
            close(dataFd);
            return false;
        }
        client.data.DataFd = dataFd;
        return true;
    }

    return false;
}

static void resetDataChannel(ClientSession& client)
{
    if (client.data.listenFd != -1) close(client.data.listenFd);
    if (client.data.DataFd != -1) close(client.data.DataFd);
    client.data.listenFd = -1;
    client.data.DataFd = -1;
    client.data.mode = NONE;
    client.data.peerAddr = sockaddr_in{};
}

#endif /* SERVERSTRUCTURES_HPP */
