/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CommandPasv.hpp
*/
#ifndef COMMANDPASV_HPP
#define COMMANDPASV_HPP

#include "ACommand.hpp"
#include "Socket.hpp"
#include "Server.hpp"

static std::string make227(const sockaddr_in& localAddr, uint16_t port)
{
    uint32_t ip = ntohl(localAddr.sin_addr.s_addr);
    int h1 = (ip >> 24) & 0xFF;
    int h2 = (ip >> 16) & 0xFF;
    int h3 = (ip >> 8) & 0xFF;
    int h4 = ip & 0xFF;
    int p1 = port / 256;
    int p2 = port % 256;

    std::ostringstream oss;
    oss << "227 Entering Passive Mode ("
        << h1 << "," << h2 << "," << h3 << "," << h4 << ","
        << p1 << "," << p2 << ").\r\n";
    return oss.str();
}

class CommandPasv : public ACommand {
  public:
    CommandPasv() = default;
    ~CommandPasv() override = default;

    void execute(const std::string& args, ClientSession client, std::vector<struct pollfd>& pollArray) override {
      if (!client.loggedIn) {
          client.responseBuffer = "530 Not logged in.\r\n";
          return;
      }
      if (!args.empty()) {
          client.responseBuffer = "501 Syntax error in parameters or arguments.\r\n";
          return;
      }

      if (client.data.listenFd != -1) {
          close(client.data.listenFd);
          client.data.listenFd = -1;
      }
      if (client.data.DataFd != -1) {
          close(client.data.DataFd);
          client.data.DataFd = -1;
      }

      int fd = socket(AF_INET, SOCK_STREAM, 0);
      if (fd < 0) {
          client.responseBuffer = "425 Can't open data connection.\r\n";
          return;
      }

      sockaddr_in addr{};
      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = htonl(INADDR_ANY);
      addr.sin_port = htons(0);

      if (bind(fd, (sockaddr*)&addr, sizeof(addr)) < 0 ||
          listen(fd, 1) < 0) {
          close(fd);
          client.responseBuffer = "425 Can't open data connection.\r\n";
          return;
      }

      socklen_t len = sizeof(addr);
      if (getsockname(fd, (sockaddr*)&addr, &len) < 0) {
          close(fd);
          client.responseBuffer = "425 Can't open data connection.\r\n";
          return;
      }

      client.data.mode = PASSIVE;
      client.data.listenFd = fd;
      client.data.DataFd = -1;

      sockaddr_in controlLocal{};
      socklen_t controlLen = sizeof(controlLocal);
      if (getsockname(client.controlFd, (sockaddr*)&controlLocal, &controlLen) < 0) {
          close(fd);
          client.data.mode = NONE;
          client.data.listenFd = -1;
          client.responseBuffer = "425 Can't open data connection.\r\n";
          return;
      }

      client.responseBuffer = make227(controlLocal, ntohs(addr.sin_port));

      struct pollfd p{};
      p.fd = fd;
      p.events = POLLIN;
      p.revents = 0;
      pollArray.push_back(p);
    }
};

#endif /* COMMANDPASV_HPP */
