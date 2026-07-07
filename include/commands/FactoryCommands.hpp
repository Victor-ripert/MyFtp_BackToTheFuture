/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** MyFtp
*/

#ifndef FACTORYCOMMANDS_HPP
    #define FACTORYCOMMANDS_HPP
    #include <string>
    #include <unordered_map>
    #include <memory>
    #include "ACommand.hpp"

class FactoryCommands {
    public:
        ACommand& getCommand(const std::string& commandName);

    private:
        static const std::unordered_map<std::string, std::unique_ptr<ACommand>> _commands;
};

#endif /* FACTORYCOMMANDS_HPP */