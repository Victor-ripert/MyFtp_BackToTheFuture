/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CommandNoop.hpp
*/
#ifndef COMMANDNOOP_HPP
#define COMMANDNOOP_HPP

#include "ACommand.hpp"

class CommandNoop : public ACommand {
  public:
    CommandNoop() = default;
    ~CommandNoop() override = default;

    void execute(const std::string& args, ClientSession client) override {
      client.responseBuffer = "200 Command okay.\n";
    }
};

#endif /* COMMANDNOOP_HPP */
