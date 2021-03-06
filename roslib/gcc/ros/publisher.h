#ifndef _TINYROS_PUBLISHER_H_
#define _TINYROS_PUBLISHER_H_

#include "tiny_ros/tinyros_msgs/TopicInfo.h"
#include "tiny_ros/ros/node_handle_base.h"
#include "tiny_ros/ros/log.h"

namespace tinyros
{

/* Generic Publisher */
class Publisher
{
public:
  Publisher(std::string topic_name, Msg * msg, int endpoint = tinyros::tinyros_msgs::TopicInfo::ID_PUBLISHER) :
    topic_(topic_name),
    msg_(msg),
    nh_(NULL),
    negotiated_(false),
    endpoint_(endpoint) { }

  int publish(const Msg * msg, bool islog = false)
  {
    if (nh_ != NULL) {
      return nh_->publish(id_, msg, islog);
    } else {
      tinyros_log_error("%s topic_name: %s, nh is NULL, please advertise.", __FUNCTION__, topic_.c_str());
      return -1;
    }
  }
  
  int getEndpointType()
  {
    return endpoint_;
  }

  bool negotiated()
  {
    return negotiated_;
  }

  std::string topic_;
  Msg *msg_;
  // id_ and no_ are set by NodeHandle when we advertise
  uint32_t id_;
  NodeHandleBase_* nh_;

  // negotiated_ is set by NodeHandle when we negotiateTopics
  bool negotiated_;

private:
  int endpoint_;
};

}

#endif
