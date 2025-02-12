#pragma once
#include <fmt/format.h>
#include <sqlpp11/sqlite3/connection_config.h>
#include <sqlpp11/sqlite3/connection_pool.h>
#include <sqlpp11/sqlite3/sqlite3.h>
#include <sqlpp11/sqlpp11.h>
#include <string>
#include <unicode/unistr.h>

inline std::shared_ptr<sqlpp::sqlite3::connection_pool> get_conn_pool_ptr() {
  using namespace sqlpp::sqlite3;
  connection_config config;
  config.debug = true;
  config.flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
  config.path_to_database =
      "/home/Ess/Desktop/Essearch/Arachne/datas/db/news.sqlite3";
  auto shared_config = std::make_shared<connection_config>(config);
  auto pool =
      std::make_shared<sqlpp::sqlite3::connection_pool>(shared_config, 8);
  return pool;
}

namespace Arachne {

#define LOG(...) fmt::println("{}", __VA_ARGS__)

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

} // namespace Arachne
