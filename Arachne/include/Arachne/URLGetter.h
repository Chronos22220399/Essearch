#pragma once
#include <Document.h>
#include <Node.h>
#include <httplib.h>
#include <queue>
#include <spdlog/spdlog.h>

namespace Arachne {

class URLGetter {
private:
  // 获取所有页面的 link
  std::vector<std::string> get_all_page_links();

public:
  URLGetter(std::shared_ptr<spdlog::logger> logger = nullptr);

  URLGetter(URLGetter &&other) = delete;

  // 获取新闻的 url
  std::vector<std::string> get_new_url();

private:
  std::shared_ptr<spdlog::logger> logger;
  const std::string domain = "https://news.hbut.edu.cn";
};
// TODO: 构建一个 url 队列，URLGetter 返回该队列

} // namespace Arachne
