#pragma once
#include <fmt/format.h>
#include <sqlpp11/sqlite3/connection_config.h>
#include <sqlpp11/sqlite3/connection_pool.h>
#include <sqlpp11/sqlite3/sqlite3.h>
#include <sqlpp11/sqlpp11.h>
#include <string>
#include <unicode/unistr.h>

#pragma once
#include <httplib.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/spdlog.h>

namespace Arachne {

namespace Autils {

#define SPFLOG_ACTIVE_LEVEL SPDLOG_LOGGER_TRACE

// #define LOG(...) fmt::println("{}", __VA_ARGS__)
#define LOG(...)                                                               \
  fmt::println("[{}:{}]: {}", __FUNCTION__, __LINE__, fmt::format(__VA_ARGS__))

// 检查出 nullptr 则直接退出
#define CHECK_INIT_AND_LOG(ptr, ...)                                           \
  {                                                                            \
    if (ptr == nullptr) {                                                      \
      LOG(__VA_ARGS__);                                                        \
      exit(-1);                                                                \
    }                                                                          \
  }

// 捕获错误的 log
#define CATCH_LOG(...)                                                         \
  fmt::println("[{}:{}]: {}", __FUNCTION__, __LINE__, fmt::format(__VA_ARGS__))

// 获取 daily logger
inline auto get_daily_logger(std::string logger_name = "/logs") {
  try {
    std::shared_ptr<spdlog::logger> regLogger = spdlog::daily_logger_mt(
        logger_name.c_str(), (logger_name + ".log").c_str());
    regLogger->set_pattern(
        "[%n][%Y-%m-%d %H:%M:%S.%e] [%l] [%s %!:%#] [%t] %v");
    regLogger->set_level(spdlog::level::debug);
    spdlog::flush_every(std::chrono::seconds(5));
    return regLogger;
  } catch (const spdlog::spdlog_ex &e) {
    LOG("日志初始化错误: {}", e.what());
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

inline std::shared_ptr<sqlpp::sqlite3::connection_pool> get_conn_pool_ptr() {
  using namespace sqlpp::sqlite3;
  connection_config config;
  config.debug = true;
  config.flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
  config.path_to_database =
      "/home/Ess/Desktop/Essearch/Arachne/datas/db/new.sqlite3";
  auto shared_config = std::make_shared<connection_config>(config);
  auto pool =
      std::make_shared<sqlpp::sqlite3::connection_pool>(shared_config, 8);
  return pool;
}

inline std::string strip(const std::string &str) {
  icu::UnicodeString ustr = icu::UnicodeString::fromUTF8(str);
  ustr.trim();
  auto result = std::string();
  ustr.toUTF8String(result);
  return result;
}

class ScopedTranscation {
  using pooled_conn_ptr = std::shared_ptr<
      sqlpp::pooled_connection<sqlpp::sqlite3::connection_base>>;

public:
  ScopedTranscation(pooled_conn_ptr conn_ptr_)
      : conn_ptr_(conn_ptr_), commited_(false) {
    conn_ptr_->start_transaction();
  };

  void commit() {
    if (!commited_) {
      conn_ptr_->commit_transaction();
      commited_ = true;
    }
  }

  ~ScopedTranscation() {
    if (!commited_ && conn_ptr_->is_transaction_active()) {
      conn_ptr_->rollback_transaction(true);
    }
  }

private:
  pooled_conn_ptr conn_ptr_;
  bool commited_;
};

struct URLChecker {
  static bool new_url_is_valid(const std::string &url) {
    if (url.length() < 8 || !url.starts_with("/info/")) {
      LOG("错误的新闻 url");
      return false;
    }
    return true;
  }

  static bool page_url_is_valid(const std::string &page_url) {
    if (page_url.length() < 8 || !page_url.starts_with("/xxxw")) {
      LOG("错误的页面 url");
      return false;
    }
    return true;
  }
};

} // namespace Autils
} // namespace Arachne
