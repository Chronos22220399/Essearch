#pragma once
#include <Arachne/Autils.hpp>
#include <Arachne/Include.h>
#include <include/News.h>
#include <sqlpp11/sqlite3/connection_pool.h>

namespace Arachne {

class NewDeleter {
private:
  class NewDelImpl {

  private:
    template <typename Deleter, typename... Args>
    new_cnt_type delete_new_generic_impl(Deleter &&deleter, Args &&...args);

  public:
    NewDelImpl(std::shared_ptr<sqlpp::sqlite3::connection_pool> pool);

    template <typename Column, typename Value>
    new_cnt_type delete_new_generic(const Value &value) const;

    new_cnt_type delete_new_generic_has(const std::string &value);

    new_cnt_type delete_all_news() const;

  private:
    std::shared_ptr<sqlpp::sqlite3::connection_pool> pool;
  };

public:
  explicit NewDeleter(std::shared_ptr<sqlpp::sqlite3::connection_pool> pool);

  new_cnt_type delete_new_by_title(const std::string &t) const;

  new_cnt_type delete_new_by_id(const size_t &id) const;

  new_cnt_type delete_new_by_url(const std::string &url) const;

  // 因为暂时用不到 cnt,而计算cnt 会对性能存在影响，故返回 {0}
  new_cnt_type delete_all_news() const;

private:
  NewDelImpl impl;
};

} // namespace Arachne
