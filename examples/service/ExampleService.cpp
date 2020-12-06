#include "tiny_ros/ros.h"
#include "tiny_ros/tinyros_hello/Test.h"

static void service_cb(const tinyros::tinyros_hello::Test::Request & req, tinyros::tinyros_hello::Test::Response & res) {
  res.output = "Hello, tiny-ros ^_^";
}

int main() {
  tinyros::init("GccExampleService", "127.0.0.1");
  tinyros::ServiceServer<tinyros::tinyros_hello::Test::Request, tinyros::tinyros_hello::Test::Response> server("test_srv", &service_cb);
  tinyros::nh()->advertiseService(server);
  while(true) {
#ifdef WIN32
    Sleep(10*1000);
#else
    sleep(10);
#endif
  }
  
  return 0;
}

