/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** CommandList.hpp
*/
#ifndef COMMANDLIST_HPP
#define COMMANDLIST_HPP

#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include "ACommand.hpp"

class CommandList : public ACommand {
  public:
    CommandList() = default;
    ~CommandList() override = default;

    void execute(const std::string& args, ClientSession client, std::vector<struct pollfd>& pollArray) override {
      (void)pollArray;
      if (!client.loggedIn) {
          client.responseBuffer = "530 Not logged in.\r\n";
          return;
      }
      if (!openDataConnection(client)) {
          client.responseBuffer = "425 Use PORT or PASV first.\r\n";
          return;
      }

      client.responseBuffer = "150 File status okay; about to open data connection.\r\n";

      pid_t pid = fork();
      if (pid == 0) {
          std::string path = args.empty() ? client.cwd : args;
          DIR* dir = opendir(path.c_str());
          if (!dir) _exit(1);

          struct dirent* ent = nullptr;
          while ((ent = readdir(dir)) != nullptr) {
              std::string line = ent->d_name;
              line += "\r\n";
              write(client.data.DataFd, line.c_str(), line.size());
          }
          closedir(dir);
          close(client.data.DataFd);
          _exit(0);
      }

      int status = 0;
      waitpid(pid, &status, 0);
      resetDataChannel(client);

      if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
          client.responseBuffer += "226 Closing data connection.\r\n";
      else
          client.responseBuffer += "451 Requested action aborted. Local error in processing.\r\n";
    }
};

#endif /* COMMANDLIST_HPP */
