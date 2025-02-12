#include <Arachne/Autils.hpp>
#include <Arachne/NewDeleter.h>
#include <Arachne/NewGetter.h>
#include <Arachne/NewParser.h>
#include <Arachne/NewSaver.h>
#include <include/News.h>
#include <sqlpp11/sqlite3/connection_config.h>
#include <sqlpp11/sqlite3/connection_pool.h>
#include <sqlpp11/sqlite3/sqlite3.h>
#include <sqlpp11/sqlpp11.h>

inline void run() {
  using namespace Arachne;
  auto pool_ptr = get_conn_pool_ptr();

  // NewDeleter deleter{pool_ptr};
  // deleter.delete_new_by_id(3);

  NewGetter getter{};
  NewParser parser{};
  NewSaver saver{pool_ptr};
  std::string url = "/info/1011/20307.htm";
  std::string n_html = getter.get_new(url);
  NewParser::New n = parser.parse(n_html, url);
  saver.save_new(n, true);
}

int main() {
  run();
  return 0;
}

// std::unique_ptr<sqlpp::sqlite3::connection_pool> get_sqlpp11_pool() {
//   using namespace sqlpp::sqlite3;
//   connection_config config;
//   config.debug = true;
//   config.flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
//   config.path_to_database = "./datas/news.sqlite3";
//   auto shared_config = std::make_shared<connection_config>(config);
//   return std::make_unique<connection_pool>(shared_config, 8);
// }
//
// void start() {
//   auto logger = Arachne::get_daily_logger();
//   auto pool = get_sqlpp11_pool();
//   Arachne::URLGetter urlGetter(logger);
//
//   std::vector<std::string> urls = urlGetter.get_new_url();
//   fmt::println("链接总数: {}", urls.size());
//   // for (auto &url : urls) {
//   // logger->info("Found URL: {}", url);
//   fmt::println("Found URL: {}", urls[0]);
//   Arachne::ContentParser contentParser(logger);
//   auto content = contentParser.resolve_news(urls[0]);
//
//   // for (auto info : content) {
//   //   fmt::println("{}", info);
//   // }
//   fmt::println("\n-------------\n爬取完毕，开始爬取下一篇:\n------------\n");
//   // TODO: 数据库存储
//   News::New new_v{};
// }
