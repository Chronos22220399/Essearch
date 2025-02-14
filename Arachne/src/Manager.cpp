#include <Arachne/Autils.hpp>
#include <Arachne/Manager.h>
#include <Arachne/NewDeleter.h>
#include <Arachne/NewGetter.h>
#include <Arachne/NewParser.h>
#include <Arachne/NewSaver.h>
#include <Arachne/URLGetter.h>
#include <include/News.h>
#include <mutex>
#include <sqlpp11/sqlite3/connection_config.h>
#include <sqlpp11/sqlite3/connection_pool.h>
#include <sqlpp11/sqlite3/sqlite3.h>
#include <sqlpp11/sqlpp11.h>
#include <tbb/parallel_for.h>

namespace Arachne {

new_cnt_type CrawlPolicy::crawl_single_new(const std::string &url) {
  auto pool_ptr = Autils::get_conn_pool_ptr();
  NewGetter getter{};
  NewParser parser{};
  NewSaver saver{pool_ptr};

  if (!Autils::URLChecker::new_url_is_valid(url)) {
    LOG("{}", "url 错误");
    return 0;
  }

  LOG("开始爬取: {} 的新闻", url);
  std::string n_html = getter.get_new(url);
  NewParser::New n = parser.parse(n_html, url);
  auto status = saver.save_new(n, false);
  if (status == NewSaver::SaveStatus::SaveSuccess) {
    LOG("成功添加：{} 的新闻", url);
    return 1;
  }
  return 0;
}

new_cnt_type CrawlNormal::crawl_all_news() {
  auto pool_ptr = Autils::get_conn_pool_ptr();
  // auto logger = Autils::get_daily_logger("./Arachne/logs/log");
  NewGetter getter{};
  NewParser parser{};
  NewSaver saver{pool_ptr};

  URLGetter urlGetter{};
  std::vector<std::string> urls(2200);
  new_cnt_type new_cnt{0};
  urlGetter.get_new_urls(urls);
  urls.shrink_to_fit();

  for (auto &url : urls) {
    if (url.empty()) {
      continue;
    } else {
      LOG("开始爬取: {} 的新闻", url);
      std::string n_html = getter.get_new(url);
      NewParser::New n = parser.parse(n_html, url);
      auto status = saver.save_new(n, false);
      if (status == NewSaver::SaveStatus::SaveSuccess) {
        LOG("成功添加：{} 的新闻", url);
        new_cnt += 1;
      }
    }
  }
  return new_cnt;
}

new_cnt_type CrawlParallelTBB::crawl_all_news() {
  auto pool_ptr = Autils::get_conn_pool_ptr();
  // auto logger = Autils::get_daily_logger("./Arachne/logs/log");

  URLGetter urlGetter{};
  std::vector<std::string> urls(2200);
  urlGetter.get_new_urls(urls);
  urls.shrink_to_fit();
  new_cnt_type new_cnt{0};

  std::mutex mt;
  tbb::parallel_for(
      tbb::blocked_range<size_t>(0, urls.size()),
      [&urls, &new_cnt, &mt, pool_ptr](tbb::blocked_range<size_t> r) {
        NewGetter getter{};
        NewParser parser{};
        NewSaver saver{pool_ptr};
        new_cnt_type new_cnt_local{0};
        for (size_t i = r.begin(); i < r.end(); ++i) {
          if (urls[i].empty()) {
            continue;
          } else {
            LOG("开始爬取: {} 的新闻", urls[i]);
            std::string n_html = getter.get_new(urls[i]);
            NewParser::New n = parser.parse(n_html, urls[i]);
            auto status = saver.save_new(n, false);
            if (status == NewSaver::SaveStatus::SaveSuccess) {
              new_cnt_local += 1;
            }
          }
        }
        std::lock_guard<std::mutex> lock(mt);
        new_cnt += new_cnt_local;
      });
  return new_cnt;
}

Manager::Manager(conn_pool_ptr pool_ptr)
    : pool_ptr(pool_ptr), crawl_policy(nullptr) {};

void Manager::set_crawl_policy(crawl_policy_ptr crawl_policy_ptr) {
  this->crawl_policy = std::move(crawl_policy_ptr);
}

new_cnt_type Manager::crawl_all_news() {
  CHECK_INIT_AND_LOG(crawl_policy, "未设置爬取策略");
  return crawl_policy->crawl_all_news();
}
new_cnt_type Manager::crawl_single_new(const std::string &url) {
  CHECK_INIT_AND_LOG(crawl_policy, "未设置爬取策略");
  return crawl_policy->crawl_single_new(url);
}

new_cnt_type Manager::delete_all_news() {
  CHECK_INIT_AND_LOG(pool_ptr, "未初始化连接词");
  NewDeleter deleter(pool_ptr);
  return deleter.delete_all_news();
}

} // namespace Arachne
