/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** MyFtp
*/

#include "commands/FactoryCommands.hpp"
#include "commands/CommandUnknown.hpp"

const std::unordered_map<std::string, std::unique_ptr<ACommand>> FactoryCommands::_commands = []() {
    std::unordered_map<std::string, std::unique_ptr<ACommand>> map;
    map["USER"] = std::make_unique<CommandUnknown>();
    map["PASS"] = std::make_unique<CommandUnknown>();
    return map;
}();

ACommand& FactoryCommands::getCommand(const std::string& commandName) {
    auto it = _commands.find(commandName);

    if (it != _commands.end()) {
        return *it->second;
    }
    //throw error
}