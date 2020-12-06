#include "tiny_ros/ros.h"
#include "tiny_ros/tinyros_hello/TinyrosHello.h"

static void subscriber_cb(const tinyros::tinyros_hello::TinyrosHello& received_msg) {
  printf("%s\n", received_msg.hello.c_str());
}

int main(int argc, char *argv[]) {
  bool isudp = false;
  std::string ipaddr = "127.0.0.1";
  if (argc >= 2) {
    ipaddr = argv[1];
  }
  if (argc >= 3) {
    isudp = atoi(argv[2]);
  }
  tinyros::init("GccExampleSubscriber", ipaddr);
  tinyros::Subscriber<tinyros::tinyros_hello::TinyrosHello> sub("tinyros_hello", subscriber_cb);
  if (!isudp) {
      tinyros::nh()->subscribe(sub);
  } else {
      tinyros::udp()->subscribe(sub);
  }
  
  while(true) {
#ifdef WIN32
    Sleep(10*1000);
#else
    sleep(10);
#endif
  }

  return 0;
}

