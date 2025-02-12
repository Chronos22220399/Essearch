#pragma once
#include <Arachne/NewParser.h>
#include <include/News.h>
#include <sqlpp11/sqlite3/connection_pool.h>

namespace Arachne {

class NewSaver {
  using pooled_conn_ptr = std::shared_ptr<
      sqlpp::pooled_connection<sqlpp::sqlite3::connection_base>>;

public:
  NewSaver(std::shared_ptr<sqlpp::sqlite3::connection_pool> pool = nullptr);

  void save_new(const NewParser::New &n, bool can_update = false);

private:
  std::shared_ptr<sqlpp::sqlite3::connection_pool> pool;
};

} // namespace Arachne
