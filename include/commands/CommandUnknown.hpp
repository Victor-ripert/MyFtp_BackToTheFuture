/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CommandUnknown.hpp
*/
#ifndef COMMANDUNKNOWNG_HPP
#define COMMANDUNKNOWNG_HPP

#include "ACommand.hpp"
#include <string>

class CommandUnknown : public ACommand {
  public:
    CommandUnknown() = default;
    ~CommandUnknown() override = default;

    void execute(const std::string& args) override {
        printf("Error: Unknown command or bad parameters received");
    }
};

#endif /* COMMANDUNKNOWN_HPP */
