#pragma once
#include <Document.h>
#include <Node.h>
#include <httplib.h>
#include <spdlog/spdlog.h>

namespace Arachne {

class URLGetter {
private:
  class URLGetterParser {
    // 将url修正：从 https://news.hbut.edu.cn/xxxw/91.htm 获取的大部分 url
    // 会是类似 ../info/1011/20310.htm 的形式，因此要将 .. 删去
    auto amend_url(const std::string &url);

  public:
    std::vector<std::string> parse_new_url(std::string body);

  private:
    CDocument doc;
  };

  // 获取所有页面的 link
  std::vector<std::string> get_all_page_links();

public:
  // URLGetter(std::shared_ptr<spdlog::logger> logger = nullptr);
  URLGetter();

  URLGetter(URLGetter &&other) = delete;

  // 获取新闻的 url
  void get_new_urls(std::vector<std::string> &urls);

private:
  // std::shared_ptr<spdlog::logger> logger;
  const std::string domain = "https://news.hbut.edu.cn";
};

} // namespace Arachne
