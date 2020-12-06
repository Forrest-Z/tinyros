#ifndef _TINYROS_LOG_H_
#define _TINYROS_LOG_H_

#include "tiny_ros/ros/time.h"
#include "tiny_ros/tinyros_msgs/Log.h"

namespace tinyros
{
void mtrace(int level, const char *chfr, ...);

#define tinyros_log_info(format, ...) tinyros::mtrace(tinyros::tinyros_msgs::Log::ROSINFO, format, ##__VA_ARGS__)
#define tinyros_log_warn(format, ...) tinyros::mtrace(tinyros::tinyros_msgs::Log::ROSWARN, format, ##__VA_ARGS__)
#define tinyros_log_error(format, ...) tinyros::mtrace(tinyros::tinyros_msgs::Log::ROSERROR, format, ##__VA_ARGS__)
#define tinyros_log_debug(format, ...) tinyros::mtrace(tinyros::tinyros_msgs::Log::ROSDEBUG, format, ##__VA_ARGS__)

#define TINYROS_LOG_ONCE_TIME_THROTTLE  1
#define tinyros_log_once_info(format, ...) { \
  static double __once_time = -1.0f; \
  if(__once_time < 0.0f) \
    __once_time = tinyros::Time::now().toSec(); \
  double __once_tem_sec =(tinyros::Time::now().toSec() - __once_time); \
  if((__once_tem_sec > TINYROS_LOG_ONCE_TIME_THROTTLE) || (__once_tem_sec < 0.0f)) { \
    __once_time = tinyros::Time::now().toSec(); \
    tinyros::mtrace(tinyros::tinyros_msgs::Log::ROSINFO, format, ##__VA_ARGS__); \
  } \
}
#define tinyros_log_once_warn(format, ...) { \
  static double __once_time = -1.0f; \
  if(__once_time < 0.0f) \
    __once_time = tinyros::Time::now().toSec(); \
  double __once_tem_sec =(tinyros::Time::now().toSec() - __once_time); \
  if((__once_tem_sec > TINYROS_LOG_ONCE_TIME_THROTTLE) || (__once_tem_sec < 0.0f)) { \
    __once_time = tinyros::Time::now().toSec(); \
    tinyros::mtrace(tinyros::tinyros_msgs::Log::ROSWARN, format, ##__VA_ARGS__); \
  } \
}
#define tinyros_log_once_error(format, ...) { \
  static double __once_time = -1.0f; \
  if(__once_time < 0.0f) \
    __once_time = tinyros::Time::now().toSec(); \
  double __once_tem_sec =(tinyros::Time::now().toSec() - __once_time); \
  if((__once_tem_sec > TINYROS_LOG_ONCE_TIME_THROTTLE) || (__once_tem_sec < 0.0f)) { \
    __once_time = tinyros::Time::now().toSec(); \
    tinyros::mtrace(tinyros::tinyros_msgs::Log::ROSERROR, format, ##__VA_ARGS__); \
  } \
}
#define tinyros_log_once_debug(format, ...) { \
  static double __once_time = -1.0f; \
  if(__once_time < 0.0f) \
    __once_time = tinyros::Time::now().toSec(); \
  double __once_tem_sec =(tinyros::Time::now().toSec() - __once_time); \
  if((__once_tem_sec > TINYROS_LOG_ONCE_TIME_THROTTLE) || (__once_tem_sec < 0.0f)) { \
    __once_time = tinyros::Time::now().toSec(); \
    tinyros::mtrace(tinyros::tinyros_msgs::Log::ROSDEBUG, format, ##__VA_ARGS__); \
  } \
}

}  // namespace tinyros

#endif


