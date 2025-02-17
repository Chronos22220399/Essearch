#include <Arachne/Autils.hpp>
#include <Arachne/Manager.h>
#include <fmt/format.h>
#include <include/News.h>

using namespace Arachne::Autils;

class DBHelper {
  using pooled_conn_type = sqlpp::sqlite3::pooled_connection;
  using pooled_conn_ptr_type = std::shared_ptr<pooled_conn_type>;

public:
  DBHelper(pooled_conn_ptr_type pooled_conn_ptr)
      : pooled_conn_ptr(pooled_conn_ptr) {}

  template <typename DBOperation, typename... Args>
  auto run(DBOperation &&operation, Args &&...args) {
    try {
      if (!pooled_conn_ptr->is_connected()) {
        LOG("{}", "数据库未连接");
        return 0;
      }
      ScopedTranscation trans{pooled_conn_ptr};
      auto ret = operation(std::forward<Args>(args)...);
      trans.commit();
      return ret;
    } catch (const sqlpp::exception &e) {
      LOG("删除时出现数据库错误: {}", e.what());
    } catch (const std::exception &e) {
      LOG("删除时出现系统错误: {}", e.what());
    }
    return 0;
  }

private:
  pooled_conn_ptr_type pooled_conn_ptr;
};

size_t
delete_new_generic_impl(std::shared_ptr<sqlpp::sqlite3::connection_pool> pool) {
  auto pooled_conn_ptr =
      std::make_shared<sqlpp::sqlite3::pooled_connection>(pool->get());
  DBHelper helper{pooled_conn_ptr};
  helper.run([pooled_conn_ptr]() {
    News::New nw{};
    (*pooled_conn_ptr)(remove_from(nw).where(nw.newId == 1));
    return 1;
  });
  return 0;
}

int main() {
  using namespace Arachne::Autils;
  auto pool = get_conn_pool_ptr();
  delete_new_generic_impl(pool);

  // auto conn_ptr = get_conn_pool_ptr();
  // Arachne::Manager manager(conn_ptr);
  // manager.delete_all_news();
  // manager.set_crawl_policy();
  // manager.crawl_single_new("/info/1011/20322.htm");

  return 0;
}
