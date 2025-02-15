#pragma once
#include <Arachne/Include.h>
#include <memory>
#include <sqlpp11/sqlite3/connection_pool.h>

namespace Arachne {

class CrawlPolicy {
protected:
public:
  // 爬取网站上所有新闻（尽量）
  virtual new_cnt_type crawl_all_news() = 0;
  // 爬取某一页面的新闻
  virtual new_cnt_type crawl_one_page_news(const std::string &page_url) = 0;
  // 爬取给出的 url 对应的新闻
  virtual new_cnt_type crawl_single_new(const std::string &url);
  virtual ~CrawlPolicy() = default;
};

class CrawlNormal : public CrawlPolicy {
public:
  // 爬取网站上所有新闻（尽量）
  new_cnt_type crawl_all_news() override;
  // 爬取某一页面的新闻
  new_cnt_type crawl_one_page_news(const std::string &url) override;
};

class CrawlParallelTBB : public CrawlPolicy {
public:
  // 爬取网站上所有新闻（尽量）
  new_cnt_type crawl_all_news() override;
  // 爬取某一页面的新闻
  new_cnt_type crawl_one_page_news(const std::string &url) override;
};

class Manager {

public:
  using crawl_policy_ptr = std::unique_ptr<CrawlPolicy>;
  using conn_pool_ptr = std::shared_ptr<sqlpp::sqlite3::connection_pool>;

  Manager(conn_pool_ptr pool_ptr);

  void set_crawl_policy(
      crawl_policy_ptr crawl_policy_ptr = std::make_unique<CrawlParallelTBB>());

  new_cnt_type crawl_all_news();

  new_cnt_type crawl_single_new(const std::string &url);

  new_cnt_type delete_all_news();

private:
  // std::shared_ptr<spdlog::logger> logger;
  crawl_policy_ptr crawl_policy;

  conn_pool_ptr pool_ptr;
};

} // namespace Arachne
