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

    ClientSession() : controlFd(-1), loggedIn(false), username(""), cwd("/"), data(), inputBuffer("") {}
};

#endif /* SERVERSTRUCTURES_HPP */
