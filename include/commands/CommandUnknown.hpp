/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CommandUnknown.hpp
*/
#ifndef COMMANDUNKNOWN_HPP
#define COMMANDUNKNOWN_HPP

#include "ACommand.hpp"

class CommandUnknown : public ACommand {
  public:
    CommandUnknown() = default;
    ~CommandUnknown() override = default;

    void execute(const std::string& args, ClientSession client, std::vector<struct pollfd>& pollArray) override {
        printf("Error: Client %s received an unknown command or bad parameters.\n", client.username);
    }
};

#endif /* COMMANDUNKNOWN_HPP */
