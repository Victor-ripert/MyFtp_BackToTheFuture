/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CommandQuit.hpp
*/
#ifndef COMMANDQUIT_HPP
#define COMMANDQUIT_HPP

#include "ACommand.hpp"

class CommandQuit : public ACommand {
  public:
    CommandQuit() = default;
    ~CommandQuit() override = default;

    void execute(const std::string& args, ClientSession client) override {
      if (!client.loggedIn) {
        client.responseBuffer = "530 Not logged in.\n";
        return;
      }
      client.loggedIn = false;
      client.responseBuffer = "221 Service closing control connection.\n";
    }
};

#endif /* COMMANDQUIT_HPP */
