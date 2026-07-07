/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** MyFtp BTTF
*/

#include "Socket.hpp"

Socket::Socket(int port) : _port(port) {
    _socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(_port);
    bind(_socket_fd, (struct sockaddr*)&_address, sizeof(_address));
    listen(_socket_fd, 10);
}

int Socket::getSocketFd() {
    return _socket_fd;
}

int Socket::getPollFdIndex() {
    return _pollfdIndex;
}

void Socket::addPollFdIndex(int index) {
    _pollfdIndex = index;
}