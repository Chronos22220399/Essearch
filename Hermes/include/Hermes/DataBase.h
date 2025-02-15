#pragma once
#define SQLITE_ENABLE_STAT3
#define SQLITE_ENABLE_STAT4
#include <fmt/format.h>
#include <include/admin.h>
#include <memory>
#include <optional>
#include <sqlpp11/sqlite3/connection.h> // 如果是 SQLite3 数据库
#include <sqlpp11/sqlite3/sqlite3.h>
#include <sqlpp11/sqlpp11.h>

// struct Admin {
//   std::string username;
//   std::string password;
//   std::optional<std::string> token{std::nullopt};
// };

class DataBase {
public:
  // virtual bool query_admin(const Admin &admin) = 0;
};

class DataBase_Sqlite : DataBase {
  // bool query_admin(const Admin &admin);
};

struct Save_Success {};

inline std::unique_ptr<sqlpp::sqlite3::connection> get_sqlite3_connection(
    const std::string &path = "./datas/sqlite3/admin.sqlite3") {
  sqlpp::sqlite3::connection_config config{};
  config.path_to_database = path;
  config.flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
  config.debug = true;
  return std::make_unique<sqlpp::sqlite3::connection>(config);
}

inline std::optional<Save_Success>
save_userinfo(const std::string &hashed_username,
              const std::string &hashed_password,
              std::unique_ptr<sqlpp::sqlite3::connection> &db_ptr) {
  try {
    Admin_::Admin admin;
    (*db_ptr)(insert_into(admin).set(admin.username = hashed_username,
                                     admin.password = hashed_password));
  } catch (const std::exception &e) {
    fmt::println("保存失败: {}", e.what());
    return std::nullopt;
  }
  return {Save_Success{}};
}

inline std::optional<bool>
username_in_db(const std::string &username,
               std::unique_ptr<sqlpp::sqlite3::connection> &db_ptr) {
  Admin_::Admin admin;
  try {
    // auto prepared_statement =
    // db_ptr->prepare(select(all_of(admin)).from(admin).where(admin.username ==
    // parameter(admin.username))); prepared_statement.params.username =
    // username;
    auto res = (*db_ptr)(
        select(admin.username).from(admin).where(admin.username == username));
    return {!res.empty()};
  } catch (const std::exception &e) {
    fmt::println("出现错误: {}", e.what());
    return std::nullopt;
  }
  return true;
}
