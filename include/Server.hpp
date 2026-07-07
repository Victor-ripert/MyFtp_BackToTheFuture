/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** MyFtp BTTF
*/

#ifndef SERVER_HPP
    #define SERVER_HPP
    #include <unistd.h>
    #include <sstream>
    #include "ServerStructures.hpp"
    #include "Socket.hpp"
    #include "commands/FactoryCommands.hpp"

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
        void handleSend();
};

#endif /* SERVER_HPP */
