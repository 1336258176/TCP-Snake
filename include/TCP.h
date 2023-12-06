//
// Created by lybin on 2023/12/3.
//

#ifndef TCP_SNAKE__TCP_H_
#define TCP_SNAKE__TCP_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <memory.h>
#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>
#include <boost/log/trivial.hpp>

class TCP {
 private:
  //作为服务端
  int socket_serv;
  sockaddr_in serv_addr;
  //服务端到客户端通信socket
  int accepted_socket;
  //连接到的客户端
  sockaddr_in accepted_sockadrr;

  //作为客户端
  int socket_cli;
  sockaddr_in cli2serv_addr;

 public:
  TCP()
  {
    socket_serv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    socket_cli = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&cli2serv_addr, 0, sizeof(cli2serv_addr));
    memset(&accepted_sockadrr, 0, sizeof(accepted_sockadrr));
  }
  ~TCP()
  {
    close(socket_serv);
    close(socket_cli);
    close(accepted_socket);
  }

  //服务端
  [[nodiscard]] int GetServ2CliSocket() const
  { return accepted_socket; }
  void InitServ(const char *ip, int port);
  void StartServ(int queue_length = 20);
  void SendMsg(std::string &msg) const;

  //客户端
  [[nodiscard]] int GetCliSocket() const
  { return socket_cli; }
  void InitCli(const char *ip, int port);
  [[nodiscard]] std::string Receive() const;
};

#endif //TCP_SNAKE__TCP_H_
