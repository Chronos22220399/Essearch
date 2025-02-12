#pragma once
#include <Arachne/Autils.hpp>
#include <include/News.h>
#include <sqlpp11/sqlite3/connection_pool.h>

namespace Arachne {

class NewDeleter {
private:
  class NewDelImpl {

  public:
    NewDelImpl(std::shared_ptr<sqlpp::sqlite3::connection_pool> pool);

    bool delete_new_generic_impl(std::function<void()> deleter);

    template <typename Column, typename Value>
    bool delete_new_generic(const Value &value) const;

    bool delete_new_generic_has(const std::string &value);

  private:
    std::shared_ptr<sqlpp::sqlite3::connection_pool> pool;
  };

public:
  NewDeleter(std::shared_ptr<sqlpp::sqlite3::connection_pool> pool);

  bool delete_new_by_title(const std::string &t) const;

  bool delete_new_by_id(const size_t &id) const;

  bool delete_new_by_url(const std::string &url) const;

private:
  NewDelImpl impl;
};

} // namespace Arachne
