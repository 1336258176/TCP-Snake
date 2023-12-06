//
// Created by lybin on 2023/12/3.
//

#include "../include/TCP.h"

void TCP::InitServ(const char *ip, int port)
{
  BOOST_LOG_TRIVIAL(info) << "initializing server ...";
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(ip);
  serv_addr.sin_port = htons(port);
  if (bind(socket_serv, (struct sockaddr *) (&serv_addr), sizeof(serv_addr))) {
    BOOST_LOG_TRIVIAL(error) << "failed to bind server port ...";
    std::abort();
  }
}

void TCP::StartServ(int queue_length)
{
  BOOST_LOG_TRIVIAL(info) << "start server ...";
  if (listen(socket_serv, queue_length)) {
    BOOST_LOG_TRIVIAL(error) << "failed to listen port ...";
    abort();
  }
  socklen_t accepted_sock_addr_size = sizeof(accepted_sockadrr);
  // This function is blocking
  accepted_socket = accept(socket_serv,
                           (struct sockaddr *) (&accepted_sockadrr),
                           &accepted_sock_addr_size);
  if (accepted_socket == -1) {
    BOOST_LOG_TRIVIAL(error) << "server failed to accept ...";
    abort();
  }
}

void TCP::InitCli(const char *ip, int port)
{
  cli2serv_addr.sin_family = AF_INET;
  cli2serv_addr.sin_addr.s_addr = inet_addr(ip);
  cli2serv_addr.sin_port = htons(port);
  if (connect(socket_cli,
              (struct sockaddr *) &cli2serv_addr,
              sizeof(cli2serv_addr))) {
    BOOST_LOG_TRIVIAL(error) << "failed to connect to the server ...";
    std::abort();
  }
}

void TCP::SendMsg(std::string &msg) const
{
  BOOST_LOG_TRIVIAL(info) << "sending msg ...";
  ssize_t written_byte =
      write(accepted_socket, msg.c_str(), sizeof(char) * (msg.size() + 1));
  if (written_byte == -1) {
    BOOST_LOG_TRIVIAL(error) << "failed to send msg as server ...";
    abort();
  }
}

std::string TCP::Receive() const
{
  BOOST_LOG_TRIVIAL(info) << "received msg ...";
  char buffer[100];
  ssize_t read_byte = read(socket_cli, buffer, sizeof(buffer));
  if (read_byte == -1) {
    BOOST_LOG_TRIVIAL(error) << "failed to read msg as client ...";
  }
  return std::move(std::string(buffer));
}
