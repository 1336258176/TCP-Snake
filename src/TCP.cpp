//
// Created by lybin on 2023/12/3.
//

#include "../include/TCP.h"

void TCP::InitServ(const char *ip, int port)
{
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(ip);
  serv_addr.sin_port = htons(port);
  if (bind(socket_serv,
           reinterpret_cast<const sockaddr *>(&serv_addr),
           sizeof(serv_addr))) {
    std::cerr << "Failed to bind a port as a server.\n";
    std::abort();
  }
}

void TCP::StartServ(int queue_length)
{
  listen(socket_serv, queue_length);
  socklen_t accepted_sock_addr_size = sizeof(accepted_sockadrr);
  accepted_socket = accept(socket_serv,
                           (struct sockaddr *) (&accepted_sockadrr),
                           &accepted_sock_addr_size);
}

void TCP::InitCli(const char *ip, int port)
{
  cli2serv_addr.sin_family = AF_INET;
  cli2serv_addr.sin_addr.s_addr = inet_addr(ip);
  cli2serv_addr.sin_port = htons(port);
  if (connect(socket_cli,
              (struct sockaddr *) &cli2serv_addr,
              sizeof(cli2serv_addr))) {
    std::cerr << "Failed to connect to the server as a client.\n";
    std::abort();
  }
}
