#include <Arachne/Autils.hpp>
#include <Arachne/Manager.h>
#include <fmt/format.h>
#include <include/News.h>

using namespace Arachne::Autils;

// size_t
// delete_new_generic_impl(std::shared_ptr<sqlpp::sqlite3::connection_pool>
// pool) {
//   DBHelper helper{};
//   auto func = [](decltype(pooled_conn_ptr) p_c_ptr, int value) {
//     News::New nw{};
//     (*p_c_ptr)(remove_from(nw).where(nw.newId == value));
//     return 1;
//   };
//   helper.execute(pool, func, 1);
//   return 0;
// }

// template <typename Column, typename Value>
// new_cnt_type
// NewDeleter::NewDelImpl::delete_new_generic(const Value &value) const {
//   pooled_conn_ptr_type pooled_conn_ptr =
//       std::make_shared<sqlpp::sqlite3::pooled_connection>(pool->get());
//   auto func = [](pooled_conn_ptr_type &pooled_conn_ptr, const Value &value) {
//     News::New nw{};
//     Column column_ptr{};
//     return (*pooled_conn_ptr)(remove_from(nw).where(nw.*column_ptr ==
//     value));
//   };
//   Autils::DBHelper helper{pooled_conn_ptr};
//   helper.execute(pooled_conn_ptr, func, value);
//   // return delete_new_generic_impl<decltype(deleter), void>(deleter);
//   // return conn(remove_from(nw).where(nw.*column_ptr == value));
// }

int main() {
  using namespace Arachne::Autils;
  // auto pool = get_conn_pool_ptr();
  // delete_new_generic_impl(pool);

  auto conn_ptr = get_conn_pool_ptr();
  Arachne::Manager manager(conn_ptr);
  manager.delete_all_news();
  manager.set_crawl_policy();
  // manager.crawl_single_new("/info/1011/20322.htm");

  return 0;
}
