#include <Hermes/Eutils.hpp>
#include <Hermes/Sqlite3.h>
#include <include/admin.h>

// construct database
Hermes::Sqlite3::Sqlite3(std::shared_ptr<spdlog::logger> logger,
                         const std::string &path)
    : logger(logger) {
  if (logger == nullptr) {
    CATCH_LOG("日志句柄初始化失败");
    exit(-1);
  }
  sqlpp::sqlite3::connection_config config{};
  config.path_to_database = path;
  config.flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
  config.debug = true;
  db_ptr = std::make_unique<sqlpp::sqlite3::connection>(config);
}

// std::optional<Admin_::Admin>
// DataBase_Sqlite::query_admin(const std::string &username) {
//   try {
//
//   } catch (const std::exception &e) {
//   }
// }

// save admin info(username, password after hashed)
std::optional<Hermes::Save_Success>
Hermes::Sqlite3::save_admininfo(const std::string &username,
                                const std::string &hashed_password) {
  try {
    Admin_::Admin admin;
    (*db_ptr)(insert_into(admin).set(admin.username = username,
                                     admin.password = hashed_password));
  } catch (const std::exception &e) {
    SPDLOG_LOGGER_ERROR(logger, "保存失败: {}", e.what());
    return std::nullopt;
  }
  return {Save_Success{}};
}

// query username
std::optional<bool>
Hermes::Sqlite3::username_in_db(const std::string &username) {
  Admin_::Admin admin;
  try {
    // auto prepared_statement =
    // db_ptr->prepare(select(all_of(admin)).from(admin).where(admin.username
    // == parameter(admin.username))); prepared_statement.params.username =
    // username;
    auto res = (*db_ptr)(
        select(admin.username).from(admin).where(admin.username == username));
    return {!res.empty()};
  } catch (const std::exception &e) {
    SPDLOG_LOGGER_ERROR(logger, "出现错误: {}", e.what());
    return std::nullopt;
  }
  return true;
}
