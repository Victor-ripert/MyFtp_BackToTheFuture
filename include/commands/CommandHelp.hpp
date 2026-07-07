/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CommandHelp.hpp
*/
#ifndef COMMANDHELP_HPP
#define COMMANDHELP_HPP

#include "ACommand.hpp"

class CommandHelp : public ACommand {
  public:
    CommandHelp() = default;
    ~CommandHelp() override = default;

    void execute(const std::string& args, ClientSession client) override {
      client.responseBuffer = "214 Help message. On how to use the server or the meaning of a particular non-standard command.  This reply is useful only to the human user.\n";
    }
};

#endif /* COMMANDHELP_HPP */
