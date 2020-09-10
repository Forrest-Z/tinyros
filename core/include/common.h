#ifndef TINY_ROS_COMMON_H
#define TINY_ROS_COMMON_H
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#undef spdlog_trace
#define spdlog_trace spdlog::get("logger")->trace

#undef spdlog_debug
#define spdlog_debug spdlog::get("logger")->debug

#undef spdlog_info
#define spdlog_info spdlog::get("logger")->info

#undef spdlog_warn
#define spdlog_warn spdlog::get("logger")->warn

#undef spdlog_error
#define spdlog_error spdlog::get("logger")->error

#undef spdlog_critical
#define spdlog_critical spdlog::get("logger")->critical

#undef TCP_SERVER_PORT
#define TCP_SERVER_PORT (11315)

#undef UDP_SERVER_PORT
#define UDP_SERVER_PORT (11316)

#undef UDP_CLIENT_PORT
#define UDP_CLIENT_PORT (11317)

#undef WEB_SERVER_PORT
#define WEB_SERVER_PORT (11318)

#endif

