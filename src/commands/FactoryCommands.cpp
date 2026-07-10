/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** MyFtp
*/

#include "commands/FactoryCommands.hpp"
#include "commands/CommandUnknown.hpp"
#include "commands/CommandUser.hpp"
#include "commands/CommandPass.hpp"
#include "commands/CommandCdup.hpp"
#include "commands/CommandCwd.hpp"
#include "commands/CommandHelp.hpp"
#include "commands/CommandNoop.hpp"
#include "commands/CommandPwd.hpp"
#include "commands/CommandQuit.hpp"
#include "commands/CommandUser.hpp"

const std::unordered_map<std::string, std::unique_ptr<ACommand>> FactoryCommands::_commands = []() {
    std::unordered_map<std::string, std::unique_ptr<ACommand>> map;
    map["USER"] = std::make_unique<CommandUser>();
    map["PASS"] = std::make_unique<CommandPass>();
    map["HELP"] = std::make_unique<CommandHelp>();
    map["NOOP"] = std::make_unique<CommandNoop>();
    map["PWD"] = std::make_unique<CommandPwd>();
    map["QUIT"] = std::make_unique<CommandQuit>();
    map["CWD"] = std::make_unique<CommandCwd>();
    map["CDUP"] = std::make_unique<CommandCdup>();
    return map;
}();

ACommand& FactoryCommands::getCommand(const std::string& commandName) {
    auto it = _commands.find(commandName);

    if (it != _commands.end()) {
        return *it->second;
    }
    //throw error
}