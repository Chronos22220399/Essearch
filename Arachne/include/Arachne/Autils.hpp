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

// 统一使用 LOG 进行打印，测试阶段输出在命令行，正式部署运行阶段采用日志
// #define LOG(...) fmt::println("{}", __VA_ARGS__)
#define LOG(...)                                                               \
  fmt::println("[{}:{}]: {}", __FUNCTION__, __LINE__, fmt::format(__VA_ARGS__))

// 检查指针是否为 nullptr ,是则直接退出
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

// 获取连接池的指针
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

// 对标准库中 string 的扩展
struct ExtensionString {
  static std::string strip(const std::string &str) {
    icu::UnicodeString ustr = icu::UnicodeString::fromUTF8(str);
    ustr.trim();
    auto result = std::string();
    ustr.toUTF8String(result);
    return result;
  }
};

// URL 检查器
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

// RAII 的事务
class ScopedTranscation {
  using pooled_conn_type = sqlpp::sqlite3::pooled_connection;
  using pooled_conn_ptr_type = std::shared_ptr<pooled_conn_type>;

public:
  ScopedTranscation(pooled_conn_ptr_type pooled_conn_ptr)
      : commited_(false), pooled_conn_ptr(pooled_conn_ptr) {
    pooled_conn_ptr->start_transaction();
  };

  template <typename Func, typename... Args>
  auto run(Func &&func, Args &&...args) {
    return func(std::forward<Args>(args)...);
  }

  void commit() {
    if (!commited_) {
      pooled_conn_ptr->commit_transaction();
      commited_ = true;
    }
  }

  ~ScopedTranscation() {
    if (!commited_ && pooled_conn_ptr->is_transaction_active()) {
      pooled_conn_ptr->rollback_transaction(true);
    }
  }

private:
  bool commited_;
  pooled_conn_ptr_type pooled_conn_ptr;
};

// 对 db 使用时的公共逻辑进行提取
class DBHelper {
public:
  using conn_pool_type = sqlpp::sqlite3::connection_pool;
  using conn_pool_ptr_type = std::shared_ptr<conn_pool_type>;
  using pooled_conn_type = sqlpp::sqlite3::pooled_connection;
  using pooled_conn_ptr_type = std::shared_ptr<pooled_conn_type>;

  template <typename DBOperation, typename... Args>
  auto execute(conn_pool_ptr_type conn_pool_ptr, DBOperation &&operation,
               Args &&...args) {
    pooled_conn_ptr_type pooled_conn_ptr =
        std::make_shared<pooled_conn_type>(conn_pool_ptr->get());
    try {
      if (!pooled_conn_ptr->is_connected()) {
        LOG("{}", "数据库未连接");
        return 0;
      }
      ScopedTranscation trans{pooled_conn_ptr};
      auto ret = operation(pooled_conn_ptr, std::forward<Args>(args)...);
      trans.commit();
      return ret;
    } catch (const sqlpp::exception &e) {
      LOG("删除时出现数据库错误: {}", e.what());
      return 0;
    } catch (const std::exception &e) {
      LOG("删除时出现系统错误: {}", e.what());
      return 0;
    }
    return 0;
  }
};

} // namespace Autils
} // namespace Arachne
