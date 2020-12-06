#include "tiny_ros/ros.h"
#include "tiny_ros/tinyros_hello/TinyrosHello.h"

int main (int argc, char *argv[]) {
  int count = 0;
  char buffer[50];
  bool isudp = false;
  std::string ipaddr = "127.0.0.1";
  if (argc >= 2) {
    ipaddr = argv[1];
  }
  if (argc >= 3) {
    isudp = atoi(argv[2]);
  }

  tinyros::init("GccExamplePublisher", ipaddr);
  tinyros::Publisher hello_pub ("tinyros_hello", new tinyros::tinyros_hello::TinyrosHello());
  if (!isudp) {
    tinyros::nh()->advertise(hello_pub);
  } else {
    tinyros::udp()->advertise(hello_pub);
  }
  
  tinyros::tinyros_hello::TinyrosHello msg;
  while (true) {
    snprintf(buffer, sizeof(buffer), "%d", count++);
    msg.hello = std::string(buffer) + ": GccHello, tiny-ros ^_^";
    hello_pub.publish (&msg);
#ifdef WIN32
    Sleep(1000);
#else
    sleep(1);
#endif
  }
  return 0;
}

