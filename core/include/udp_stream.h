#ifndef TINY_ROS_UDP_STREAM_H
#define TINY_ROS_UDP_STREAM_H

#include "stream_base.h"

namespace tinyros
{
class UdpStream: public StreamBase
{
public:
  UdpStream() : sock_fd_(-1) { }

  virtual bool open(int server_port, int client_port) {
    server_port_ = server_port;
    client_port_ = client_port;
    sock_fd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd_ < 0) {
      spdlog_error("[{0}] UdpStream::open opening socket: {1}(errno: {2})", session_id_.c_str(), strerror(errno), errno);
      return false;
    }

    int opt = 1;
    struct linger so_linger;
    so_linger.l_onoff = 1;
    so_linger.l_linger = 0;
    setsockopt(sock_fd_, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt));
    setsockopt(sock_fd_, SOL_SOCKET, SO_LINGER, (const char *)&so_linger, sizeof(so_linger));

    memset(&server_endpoint_, 0, sizeof(struct sockaddr_in));
    server_endpoint_.sin_family = AF_INET;
    server_endpoint_.sin_port = htons(server_port_);
    server_endpoint_.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock_fd_, (struct sockaddr*)&server_endpoint_, sizeof(server_endpoint_)) < 0) {
      spdlog_error("[{0}] UdpStream::open bind socket: {1}(errno: {2})", session_id_.c_str(), strerror(errno), errno);
      ::close(sock_fd_);
      sock_fd_ = -1;
      return false;
    }
    return true;
  }
  
  virtual int read_some_udp(uint8_t* data, int length, struct sockaddr_in& from) {
     socklen_t from_len = sizeof(from);
     int rv = recvfrom(sock_fd_, data, length, 0, (struct sockaddr*)&from, &from_len);
     if (rv < 0) {
      spdlog_error("[{0}] UdpStream::read_some: {1}(errno: {2})", session_id_.c_str(), strerror(errno), errno);
     }
     return (rv > 0 ? rv : 0);
  } 

  virtual int write_some_udp(uint8_t* data, int length, struct sockaddr_in& to) {
    struct sockaddr_in addr = to;
    int s = sendto(sock_fd_, data, length, 0, (struct sockaddr *)&addr, sizeof(addr));
    if(s <= 0) {
      spdlog_error("[{0}] UdpStream::write_some: {1}(errno: {2})", session_id_.c_str(), strerror(errno), errno);
      return 0;
    }
    return s;
  }

  virtual void close() {
    if (sock_fd_ > 0) {
      ::close(sock_fd_);
      sock_fd_ = -1;
    }
  }

  virtual int getFd() { return sock_fd_; }

  int sock_fd_;
  int server_port_, client_port_;
  struct sockaddr_in server_endpoint_;
};
}  // namespace

#endif  // TINY_ROS_UDP_STREAM_H
