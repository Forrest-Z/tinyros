#ifndef TINY_ROS_STREAM_BASE_H
#define TINY_ROS_STREAM_BASE_H
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "common.h"

namespace tinyros
{
class StreamBase
{
public:
  virtual bool open(int server_port, int client_port) { return false; }
  
  virtual int write_some(uint8_t* data, int length) { return -1; } 
  
  virtual int write_some_udp(uint8_t* data, int length, struct sockaddr_in& to) { return -1; } 

  virtual int read_some(uint8_t* data, int length) { return -1; }

  virtual int read_some_udp(uint8_t* data, int length, struct sockaddr_in& from) { return -1; }

  virtual int getFd() { return -1; }
  
  virtual void close() { }

  std::string session_id_;
};
}  // namespace

#endif  // TINY_ROS_STREAM_BASE_H




