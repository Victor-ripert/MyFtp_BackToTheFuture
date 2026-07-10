/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CommandRetr.hpp
*/
#ifndef COMMANDRETR_HPP
#define COMMANDRETR_HPP

#include <fcntl.h>
#include <sys/wait.h>
#include "ACommand.hpp"

class CommandRetr : public ACommand {
  public:
    CommandRetr() = default;
    ~CommandRetr() override = default;

    void execute(const std::string& args, ClientSession client, std::vector<struct pollfd>& pollArray) override {
    // (void)pollArray;
    if (!client.loggedIn) {
        client.responseBuffer = "530 Not logged in.\r\n";
        return;
    }
    if (args.empty()) {
        client.responseBuffer = "501 Syntax error in parameters or arguments.\r\n";
        return;
    }
    if (!openDataConnection(client)) {
        client.responseBuffer = "425 Use PORT or PASV first.\r\n";
        return;
    }

    client.responseBuffer = "150 File status okay; about to open data connection.\r\n";

    pid_t pid = fork();
    if (pid == 0) {
        int fd = open(args.c_str(), O_RDONLY);
        if (fd < 0) _exit(1);

        char buf[4096];
        ssize_t n = 0;
        while ((n = read(fd, buf, sizeof(buf))) > 0) {
            ssize_t off = 0;
            while (off < n) {
                ssize_t w = write(client.data.DataFd, buf + off, n - off);
                if (w <= 0) { close(fd); _exit(1); }
                off += w;
            }
        }
        close(fd);
        close(client.data.DataFd);
        _exit(0);
    }

    int status = 0;
    waitpid(pid, &status, 0);
    resetDataChannel(client);
    client.responseBuffer += (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        ? "226 Closing data connection.\r\n"
        : "451 Requested action aborted. Local error in processing.\r\n";
}
};

#endif /* COMMANDRETR_HPP */
