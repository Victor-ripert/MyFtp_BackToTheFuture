/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** MyFtp
*/

#ifndef ACOMMAND_HPP
    #define ACOMMAND_HPP
    #include <string>

class ACommand {
    public:
        virtual ~ACommand() = default;
        virtual void execute(const std::string& args) = 0;
};

#endif /* ACOMMAND_HPP */