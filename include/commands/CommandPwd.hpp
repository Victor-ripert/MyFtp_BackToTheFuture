/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CommandPwd.hpp
*/
#ifndef COMMANDPWD_HPP
#define COMMANDPWD_HPP

#include "ACommand.hpp"

class CommandPwd : public ACommand {
  public:
    CommandPwd() = default;
    ~CommandPwd() override = default;

    void execute(const std::string& args, ClientSession client, std::vector<struct pollfd>& pollArray) override {
      if (!client.loggedIn) {
        client.responseBuffer = "530 Not logged in.\n";
        return;
      }
      client.responseBuffer = "257 " + client.cwd + " created.\n";
    }
};

#endif /* COMMANDPWD_HPP */
