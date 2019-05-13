#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <string>

#include "unix_socket/unix_socket.h"


static inline void PrintUsage(void) {
  printf("Usage: jt808-command phonenum [options ...]\n"
         "Options:\n"
         "get startup/gps/cdradio/ntripcors/ntripservice/jt808service\n"
         "    terminalparameter [parameterid ...]\n"
         "set startup [gps] [cdradio] [ntripcors] [ntripservice] "
                      "[jt808service]\n"
         "    gps [LOGGGA] [LOGRMC] [LOGATT]\n"
         "    cdradio bauderate workfreqpoint recvmode formcode\n"
         "    ntripcors ip port user passwd mntpoint reportinterval\n"
         "    ntripservice ip port user passwd mntpont reportinterval\n"
         "    jt808service ip port phonenum reportinterval\n"
         "    terminalparameter [parameterid(HEX):parametervalue ...]\n"
         "upgrade system/device/gps/cdradio versionid filepath\n");

  exit(0);
}

int main(int argc, char **argv) {
  std::string command;
  char recv_buf[65536] = {0};

  if (argc < 4 || argc > 11) {
    PrintUsage();
  }

  command.clear();
  for (int i = 1; i < argc; ++i) {
    command += argv[i];
    if (i < (argc - 1))
      command += " ";
  }

  // printf("command: %s\n", command.c_str());

  int fd = ClientConnect("/tmp/jt808cmd.sock");
  if (fd > 0) {
    send(fd, command.c_str(), command.length(), 0);
    if (recv(fd, recv_buf, sizeof(recv_buf), 0) > 0)
      printf("%s\n", recv_buf);

    close(fd);
  }

  return 0;
}
