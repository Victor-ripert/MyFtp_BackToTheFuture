/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** MyFtp BTTF
*/

#ifndef SOCKET_HPP
    #define SOCKET_HPP
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <arpa/inet.h>
    #include <poll.h>

class Socket {
    private:
        int _socket_fd;
        struct sockaddr_in _address;
        int _port;
        int _pollfdIndex;

    public:
        Socket(int port);
        ~Socket();
        int getSocketFd();
        int getPollFdIndex();
        struct sockaddr_in getAdress();
        void addPollFdIndex(int index);
};

#endif /* SOCKET_HPP */