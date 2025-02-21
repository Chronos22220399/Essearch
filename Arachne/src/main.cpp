#include <Arachne/Autils.hpp>
#include <Arachne/Manager.h>
#include <Arachne/NewDeleter.h>
#include <fmt/format.h>
#include <include/News.h>
#include <iostream>

using namespace Arachne::Autils;

int main() {
  using namespace Arachne::Autils;
  auto pool = get_conn_pool_ptr();

  auto conn_ptr = get_conn_pool_ptr();
  Arachne::NewDeleter deleter{conn_ptr};
  deleter.delete_new_by_id(1);
  Arachne::Manager manager(conn_ptr);
  // manager.set_crawl_policy();
  // manager.crawl_single_new("/info/1011/20322.htm");
  return 0;
}
