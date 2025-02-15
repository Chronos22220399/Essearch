#pragma once
#define SQLITE_ENABLE_STAT3
#define SQLITE_ENABLE_STAT4
#include <fmt/format.h>
#include <include/admin.h>
#include <memory>
#include <optional>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <sqlpp11/sqlite3/connection.h> // 如果是 SQLite3 数据库
#include <sqlpp11/sqlite3/sqlite3.h>
#include <sqlpp11/sqlpp11.h>
#include <string>

namespace Hermes {

struct Admin {
  std::string username;
  std::string hashed_password;
};

struct Save_Success {};

class Sqlite3 final {
private:
  std::unique_ptr<sqlpp::sqlite3::connection> db_ptr;
  std::shared_ptr<spdlog::logger> logger;

public:
  Sqlite3(std::shared_ptr<spdlog::logger> logger = nullptr,
          const std::string &path = "./datas/sqlite3/admin.sqlite3");

  Sqlite3(Sqlite3 &&) = delete;

  std::optional<Hermes::Admin> query_admin(const std::string &username) {
    try {
      Admin_::Admin admin{};
      auto rows = (*db_ptr)(select(admin.password, admin.username)
                                .from(admin)
                                .where(admin.username == username));
      if (rows.empty()) {
        return std::nullopt;
      }
      return Admin{rows.front().username, rows.front().password};
    } catch (const std::exception &e) {
      SPDLOG_LOGGER_ERROR(logger, "查询时出现错误: {}", e.what());
      return std::nullopt;
    }
  }

  // save admin info (usrname, password after hashed)
  // if save successful then return empty structure Save_Success, else return
  // nil
  std::optional<Save_Success>
  save_admininfo(const std::string &username,
                 const std::string &hashed_password);

  // query whether username in db, if yes then return {true}, else if error
  // occurred then return nil, else return false
  std::optional<bool> username_in_db(const std::string &username);

public:
};

} // namespace Hermes
