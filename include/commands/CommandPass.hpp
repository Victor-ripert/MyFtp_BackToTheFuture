/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CommandPass.hpp
*/
#ifndef COMMANDPASS_HPP
#define COMMANDPASS_HPP

#include "ACommand.hpp"

class CommandPass : public ACommand {
  public:
    CommandPass() = default;
    ~CommandPass() override = default;

    void execute(const std::string& args, ClientSession client) override {
      if (client.loggedIn) {
        client.responseBuffer = "230 User logged in, proceed.\n";
        return;
      }
      std::istringstream iss(args);
      std::string username;
      if (!(iss >> username)) {
        client.username == username;
        client.responseBuffer = "331 User name okay, need password.\n";
        return;
      }
      //throw error;
    }
};

#endif /* COMMANDPASS_HPP */
