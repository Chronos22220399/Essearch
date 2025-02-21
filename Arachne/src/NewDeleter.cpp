#include <Arachne/Autils.hpp>
#include <Arachne/NewDeleter.h>
// #include <sqlpp11/sqlite3/sqlite3.h>
// #include <sqlpp11/sqlpp11.h>

namespace Arachne {

NewDeleter::NewDelImpl::NewDelImpl(
    std::shared_ptr<sqlpp::sqlite3::connection_pool> pool)
    : pool(pool) {}

// template <typename Deleter>
// new_cnt_type
// NewDeleter::NewDelImpl::delete_new_generic_impl(Deleter &&deleter) {
//   auto pooled_conn_ptr =
//       std::make_shared<sqlpp::sqlite3::pooled_connection>(pool->get());
//   Autils::DBHelper helper{pooled_conn_ptr};
//   return helper.run(deleter());
// }

template <typename Deleter>
new_cnt_type
NewDeleter::NewDelImpl::delete_new_generic_impl(Deleter &&deleter) {
  auto pooled_conn_ptr =
      std::make_shared<sqlpp::sqlite3::pooled_connection>(pool->get());
  Autils::DBHelper helper{pooled_conn_ptr};
  helper.execute(std::forward<Deleter>(deleter), pooled_conn_ptr);
  // helper.run([pooled_conn_ptr]() {
  //   News::New nw{};
  //   (*pooled_conn_ptr)(remove_from(nw).where(nw.newId == 1));
  //   return 1;
  // });
  return 0;
}

template <typename Column, typename Value>
new_cnt_type
NewDeleter::NewDelImpl::delete_new_generic(const Value &value) const {
  pooled_conn_ptr_type pooled_conn_ptr =
      std::make_shared<sqlpp::sqlite3::pooled_connection>(pool->get());
  auto func = [value, pooled_conn_ptr]() {
    News::New nw{};
    Column column_ptr{};
    return (*pooled_conn_ptr)(remove_from(nw).where(nw.*column_ptr == value));
  };
  Autils::DBHelper helper{pooled_conn_ptr};
  helper.execute(pooled_conn_ptr, func);
  // return delete_new_generic_impl<decltype(deleter), void>(deleter);
  // return conn(remove_from(nw).where(nw.*column_ptr == value));
}

new_cnt_type
NewDeleter::NewDelImpl::delete_new_generic_has(const std::string &value) {
  return 0;
}

// TODO: 后续可以将返回类型从 void 改为 size_t (size_type)
new_cnt_type NewDeleter::NewDelImpl::delete_all_news() const {
  auto conn = pool->get();
  // auto conn_ptr = std::make_shared<decltype(conn)>(std::move(conn));
  pooled_conn_ptr_type conn_ptr =
      std::make_shared<decltype(conn)>(std::move(conn));
  try {
    Autils::ScopedTranscation trans(std::move(conn_ptr));

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
