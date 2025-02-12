#include <Arachne/NewDeleter.h>

namespace Arachne {

NewDeleter::NewDelImpl::NewDelImpl(
    std::shared_ptr<sqlpp::sqlite3::connection_pool> pool)
    : pool(pool) {}

bool NewDeleter::NewDelImpl::delete_new_generic_impl(
    std::function<void()> deleter) {
  auto conn_ptr = std::make_shared<
      sqlpp::pooled_connection<sqlpp::sqlite3::connection_base>>(pool->get());
  try {
    // if (conn_ptr->is_connected()) {
    if (conn_ptr->is_connected()) {
      LOG("数据库未连接");
      return false;
    }
    ScopedTranscation trans{conn_ptr};
    deleter();
    trans.commit();
    return true;
  } catch (const std::exception &e) {
    LOG("删除出错: {}", e.what());
    return false;
  }
  return false;
}

template <typename Column, typename Value>
bool NewDeleter::NewDelImpl::delete_new_generic(const Value &value) const {
  auto conn = pool->get();
  try {
    if (!conn.is_connected()) {
      LOG("数据库未连接");
      return false;
    }
    News::New nw{};
    Column column_ptr;

    conn.start_transaction();
    conn(remove_from(nw).where(nw.*column_ptr == value));
    conn.commit_transaction();
    return true;
  } catch (const std::exception &e) {
    LOG("删除出错: {}", e.what());
    if (conn.is_connected()) {
      conn.rollback_transaction(false);
    }
  }
  return false;
}

bool NewDeleter::NewDelImpl::delete_new_generic_has(const std::string &value) {
  return false;
}

NewDeleter::NewDeleter(std::shared_ptr<sqlpp::sqlite3::connection_pool> pool)
    : impl(pool) {
  if (pool == nullptr) {
    LOG("连接池未初始化 -- NewDeleter");
    exit(-1);
  }
}

bool NewDeleter::delete_new_by_title(const std::string &t) const {
  // using namespace News::New_
  // Title News::New::*
  return impl.delete_new_generic<decltype(&News::New::title)>(t);
}

bool NewDeleter::delete_new_by_id(const size_t &id) const {
  return impl.delete_new_generic<decltype(&News::New::newId)>(id);
}

bool NewDeleter::delete_new_by_url(const std::string &url) const {
  return impl.delete_new_generic<decltype(&News::New::url)>(url);
}

} // namespace Arachne
