/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CommandCdup.hpp
*/
#ifndef COMMANDCDUP_HPP
#define COMMANDCDUP_HPP

#include "ACommand.hpp"

class CommandCdup : public ACommand {
  public:
    CommandCdup() = default;
    ~CommandCdup() override = default;

    void execute(const std::string& args, ClientSession client, std::vector<struct pollfd>& pollArray) override {
      if (!client.loggedIn) {
        client.responseBuffer = "530 Not logged in.\n";
        return;
      }
      if (client.cwd != "/") {
        auto last_slash = client.cwd.find_last_of('/');
        client.cwd = client.cwd.substr(0, last_slash - 1);
      }
      if (client.cwd != "") {
        client.responseBuffer = "200 Command okay.\n";
        return;
      }
      client.cwd = "/";
      client.responseBuffer = "501 Syntax error in parameters or arguments.\n";
    }
};

#endif /* COMMANDCDUP_HPP */
