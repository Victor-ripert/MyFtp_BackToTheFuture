/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CommandUser.hpp
*/
#ifndef COMMANDUSER_HPP
#define COMMANDUSER_HPP

#include "ACommand.hpp"

class CommandUser : public ACommand {
  public:
    CommandUser() = default;
    ~CommandUser() override = default;

    void execute(const std::string& args, ClientSession client, std::vector<struct pollfd>& pollArray) override {
      if (client.loggedIn) {
        client.responseBuffer = "230 User logged in, proceed.\n";
        return;
      }
      std::istringstream iss(args);
      std::string username;
      if (!(iss >> username)) {
        client.username = username;
        client.responseBuffer = "331 User name okay, need password.\n";
        return;
      }
      client.responseBuffer = "501 Syntax error in parameters or arguments.\n";
    }
};

#endif /* COMMANDUSER_HPP */
