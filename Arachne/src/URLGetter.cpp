#include <Arachne/URLGetter.h>
#include <Arachne/Utils.h>
#include <httplib.h>

namespace Arachne {

URLGetter::URLGetter(std::shared_ptr<spdlog::logger> logger) : logger(logger) {
  if (!logger) {
    CATCH_LOG("未对 logger 进行初始化");
    exit(-1);
  }
};

// 获取所有页面的 link
std::vector<std::string> URLGetter::get_all_page_links() {
  std::vector<std::string> ret;
  size_t page = 0;
  while (page < 90) {
    std::string url =
        (page == 0 ? "/xxxw.htm"
                   : "/xxxw/" + std::to_string(91 - page) + ".htm");
    ret.push_back(url);
    page += 1;
  }
  return ret;
}

// 获取新闻的 url
std::vector<std::string> URLGetter::get_new_url() {
  auto links = get_all_page_links();
  std::vector<std::string> ret(1200);
  size_t cnt = 0;
  try {
    std::vector<std::thread> pool;
    std::vector<std::vector<std::string>> htmls_content(8);

    size_t num = (links.size() + 7) / 8;
    for (size_t i = 0; i < 8; ++i) {
      size_t start = i * num;
      size_t end = std::min((i + 1) * num, links.size());
      pool.emplace_back(
          [start, end, i, &htmls_content, &links, this, cnt]() mutable {
            // HTMLParser parser(logger);
            httplib::Client cli(domain);
            while (start < end) {
              auto res = cli.Get(links[start]);
              check_http_result(res, logger);
              std::string body = res->body;
              // auto new_urls = parser.parse_new_url(body);
              // htmls_content[i].insert(htmls_content[i].end(),
              // new_urls.begin(),
              //                         new_urls.end());
              cnt += htmls_content.size();
              start += 1;
            }
          });
    }
    for (auto &thread : pool) {
      thread.join();
    }
    for (auto &htmls : htmls_content) {
      for (auto &html : htmls) {
        ret.push_back(html);
      }
    }
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
  return ret;
}

} // namespace Arachne
