#include <Arachne/Autils.hpp>
#include <Arachne/Manager.h>

int main() {
  auto crawl_policy = std::make_unique<Arachne::CrawlParallelTBB>();
  auto conn_ptr = Arachne::Autils::get_conn_pool_ptr();
  Arachne::Manager manager(conn_ptr);
  // manager.delete_all_news();
  manager.set_crawl_policy();
  manager.crawl_single_new("/info/1011/20322.htm");
  // manager.crawl_all_news();
  return 0;
}
