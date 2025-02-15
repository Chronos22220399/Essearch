#pragma once
#include <fmt/format.h>
#include <include/admin.h>
#include <sqlpp11/sqlite3/connection.h>
#include <sqlpp11/sqlpp11.h>

inline void test_sqlpp() {
  sqlpp::sqlite3::connection_config config{};
  config.path_to_database = "./datas/sqlite3/admin.sqlite3";
  config.flags = SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE;
  config.debug = true;

  try {
    sqlpp::sqlite3::connection db{config};
    Admin_::Admin admin{};
    db.execute(R"(CREATE TABLE IF NOT EXISTS Admin (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      username VARCHAR(30),
      password VARCHAR(30)
    ))");

    // add
    // db(insert_into(admin).set(admin.username = "123", admin.password =
    // "hello")); delete db(remove_from(admin).where(admin.id==1)); query

    auto query = select(all_of(admin))
                     .from(admin)
                     .flags(sqlpp::all)
                     .where(admin.id >= 1);
    for (const auto &row : db(query)) {
      fmt::println("[id: {}] - [username: {}] - [password: {}]",
                   (int64_t)row.id, (std::string)row.username,
                   (std::string)row.password);
    }
    // update
    // db(update(admin).set(admin.username="234").where(admin.id >= 10));
  } catch (const std::exception &e) {
    fmt::println("{}", e.what());
  }
}
