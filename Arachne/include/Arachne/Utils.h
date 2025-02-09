#pragma once
#include <httplib.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/spdlog.h>

namespace Arachne {

#define SPFLOG_ACTIVE_LEVEL SPDLOG_LOGGER_TRACE

// 捕获错误的 log
#define CATCH_LOG(...)                                                         \
  fmt::println("[{}:{}]: {}", __FUNCTION__, __LINE__, fmt::format(__VA_ARGS__))

// 获取 daily logger
inline auto get_daily_logger(std::string logger_name = "../logs/Arachne") {
  try {
    std::shared_ptr<spdlog::logger> regLogger = spdlog::daily_logger_mt(
        logger_name.c_str(), (logger_name + ".log").c_str());
    regLogger->set_pattern(
        "[%n][%Y-%m-%d %H:%M:%S.%e] [%l] [%s %!:%#] [%t] %v");
    regLogger->set_level(spdlog::level::debug);
    spdlog::flush_every(std::chrono::seconds(5));
    return regLogger;
  } catch (const spdlog::spdlog_ex &e) {
    CATCH_LOG("日志初始化错误: {}", e.what());
    exit(-1);
  }
}

// 检查 httplib::Result 是否为空
inline void check_http_result(const httplib::Result &result,
                              std::shared_ptr<spdlog::logger> logger) {
  if (!result) {
    logger->warn("Result 为空");
    throw std::runtime_error("http 结果为空");
  }
}
} // namespace Arachne
