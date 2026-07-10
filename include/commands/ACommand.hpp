/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** MyFtp
*/

#ifndef ACOMMAND_HPP
    #define ACOMMAND_HPP
    #include <string>
    #include <sstream>
    #include "ServerStructures.hpp"

class ACommand {
    public:
        virtual ~ACommand() = default;
        virtual void execute(const std::string& args, ClientSession client, std::vector<struct pollfd>& pollArray) = 0;
};

#endif /* ACOMMAND_HPP */