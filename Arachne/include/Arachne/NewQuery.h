#pragma once
#include <Arachne/Autils.hpp>
#include <include/News.h>
#include <memory>
#include <sqlpp11/sqlite3/connection_config.h>
#include <sqlpp11/sqlite3/connection_pool.h>
#include <sqlpp11/sqlite3/sqlite3.h>
#include <string>

namespace Arachne {

class NewQuery {
  using pooled_conn_ptr = std::shared_ptr<
      sqlpp::pooled_connection<sqlpp::sqlite3::connection_base>>;

  template <typename ColumnPtr, typename ColumnType>
  static auto generic_query(pooled_conn_ptr pool_ptr, ColumnType &&item) {
    CHECK_INIT_AND_LOG(pool_ptr, "连接池指针未初始化");
    try {
      Autils::ScopedTranscation trans(pool_ptr);

      News::New nw{};
      ColumnPtr column_ptr{};
      // TODO: 增加类型检查，确保列的类型合法
      auto url_row = (*pool_ptr)(
          select(nw.*column_ptr).from(nw).where(nw.*column_ptr == item));
      trans.commit();
      if (url_row.empty()) {
        return QueryResult::Find;
      }
      return QueryResult::NotFind;
    } catch (const sqlpp::exception &e) {
      LOG("数据库错误: {}", e.what());
      return QueryResult::DBError;
    } catch (const std::exception &e) {
      LOG("系统错误: {}", e.what());
      return QueryResult::SysError;
    }
  };

public:
  enum class QueryResult { Find, NotFind, DBError, SysError };

  static auto url_in_db(pooled_conn_ptr pool_ptr, const std::string &url) {
    CHECK_INIT_AND_LOG(pool_ptr, "连接池指针未初始化");
    try {
      Autils::ScopedTranscation trans(pool_ptr);

      News::New nw{};
      auto url_row = (*pool_ptr)(select(nw.url).from(nw).where(nw.url == url));
      trans.commit();
      if (url_row.empty()) {
        return QueryResult::Find;
      }
      return QueryResult::NotFind;
    } catch (const sqlpp::exception &e) {
      LOG("数据库错误: {}", e.what());
      return QueryResult::DBError;
    } catch (const std::exception &e) {
      LOG("系统错误: {}", e.what());
      return QueryResult::SysError;
    }
  };
};

} // namespace Arachne
