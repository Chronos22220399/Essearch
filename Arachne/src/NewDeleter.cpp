#include <Arachne/NewDeleter.h>
// #include <sqlpp11/sqlite3/sqlite3.h>
// #include <sqlpp11/sqlpp11.h>

namespace Arachne {

NewDeleter::NewDelImpl::NewDelImpl(
    std::shared_ptr<sqlpp::sqlite3::connection_pool> pool)
    : pool(pool) {}

new_cnt_type
NewDeleter::NewDelImpl::delete_new_generic_impl(std::function<void()> deleter) {
  auto conn_ptr = std::make_shared<
      sqlpp::pooled_connection<sqlpp::sqlite3::connection_base>>(pool->get());
  try {
    if (conn_ptr->is_connected()) {
      LOG("{}", "数据库未连接");
      return 0;
    }
    Autils::ScopedTranscation trans{conn_ptr};
    deleter();
    trans.commit();
    return 1;
  } catch (const sqlpp::exception &e) {
    LOG("删除时出现数据库错误: {}", e.what());
  } catch (const std::exception &e) {
    LOG("删除时出现系统错误: {}", e.what());
    // if (conn.is_connected()) {
    //   conn.rollback_transaction(false);
    // }
  }
  return 0;
}

template <typename Column, typename Value>
new_cnt_type
NewDeleter::NewDelImpl::delete_new_generic(const Value &value) const {
  auto conn = pool->get();
  try {
    if (!conn.is_connected()) {
      LOG("{}", "数据库未连接");
      return false;
    }
    News::New nw{};
    Column column_ptr{};

    conn.start_transaction();
    conn(remove_from(nw).where(nw.*column_ptr == value));
    conn.commit_transaction();
    return 1;
  } catch (const sqlpp::exception &e) {
    LOG("删除时出现数据库错误: {}", e.what());
    return 0;
  } catch (const std::exception &e) {
    LOG("删除时出现系统错误: {}", e.what());
    // if (conn.is_connected()) {
    //   conn.rollback_transaction(false);
    // }
    return 0;
  }
}

new_cnt_type
NewDeleter::NewDelImpl::delete_new_generic_has(const std::string &value) {
  return 0;
}

// TODO: 后续可以将返回类型从 void 改为 size_t (size_type)
new_cnt_type NewDeleter::NewDelImpl::delete_all_news() const {
  auto conn = pool->get();
  auto conn_ptr = std::make_shared<decltype(conn)>(std::move(conn));
  try {
    Autils::ScopedTranscation trans(conn_ptr);

    // 删除全部
    (*conn_ptr).execute("DELETE FROM New;");
    (*conn_ptr).execute("DELETE FROM sqlite_sequence WHERE name='New';");
    trans.commit();
  } catch (const sqlpp::exception &e) {
    LOG("删除时出现数据库错误: {}", e.what());
  } catch (const std::exception &e) {
    LOG("删除时出现系统错误: {}", e.what());
  }
  return {};
};

NewDeleter::NewDeleter(std::shared_ptr<sqlpp::sqlite3::connection_pool> pool)
    : impl(pool) {
  CHECK_INIT_AND_LOG(pool, "{}", "连接池未初始化 -- NewDeleter");
}

new_cnt_type NewDeleter::delete_new_by_title(const std::string &t) const {
  // using namespace News::New_
  // Title News::New::*
  return impl.delete_new_generic<decltype(&News::New::title)>(t);
}

new_cnt_type NewDeleter::delete_new_by_id(const size_t &id) const {
  return impl.delete_new_generic<decltype(&News::New::newId)>(id);
}

new_cnt_type NewDeleter::delete_new_by_url(const std::string &url) const {
  return impl.delete_new_generic<decltype(&News::New::url)>(url);
}

new_cnt_type NewDeleter::delete_all_news() const {
  return impl.delete_all_news();
}
} // namespace Arachne
