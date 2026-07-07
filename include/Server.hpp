/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** MyFtp BTTF
*/

#ifndef SERVER_HPP
    #define SERVER_HPP
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <arpa/inet.h>
    #include <poll.h>
    #include <vector>
    #include <string>
    #include <unistd.h>
    #include <sstream>
    #include "Socket.hpp"
    #include "commands/FactoryCommands.hpp"

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
    short events;

    ClientSession() : controlFd(-1), loggedIn(false), username(""), cwd("/"), data(), inputBuffer("") {}
};

class Server {
    private:
        std::vector<struct pollfd> _pollArray;
        std::vector<ClientSession> _clientVector;
        Socket _control_socket;
        int _pollArraySize;
        int _port;

    public:
        Server(int port);
        ~Server();
        void addSocketToPoll(Socket obj);
        void doPoll();
        void acceptClient();
        void handleEvent();
        void handleCommand();
};

#endif /* SERVER_HPP */
