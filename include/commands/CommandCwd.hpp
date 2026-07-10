/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CommandCwd.hpp
*/
#ifndef COMMANDCWD_HPP
#define COMMANDCWD_HPP

#include "ACommand.hpp"

class CommandCwd : public ACommand {
  public:
    CommandCwd() = default;
    ~CommandCwd() override = default;

    void execute(const std::string& args, ClientSession client, std::vector<struct pollfd>& pollArray) override {
      if (!client.loggedIn) {
        client.responseBuffer = "530 Not logged in.\n";
        return;
      }
      std::istringstream iss(args);
      std::string cwd;
      if (!(iss >> cwd)) {
        client.cwd = cwd;
        client.responseBuffer = "250 Requested file action okay, completed.\n";
        return;
      }
      client.responseBuffer = "501 Syntax error in parameters or arguments.\n";
    }
};

#endif /* COMMANDCWD_HPP */
