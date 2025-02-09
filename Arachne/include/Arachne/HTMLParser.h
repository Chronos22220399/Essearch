#pragma once
#include <Arachne/Utils.h>
#include <Document.h>
#include <Node.h>
#include <spdlog/spdlog.h>

namespace Arachne {

class HTMLParser {
  // 将url修正：从 https://news.hbut.edu.cn/xxxw/91.htm 获取的大部分 url
  // 会是类似 ../info/1011/20310.htm 的形式，因此要将 .. 删去
  void amend_url(std::string &url);

public:
  HTMLParser(std::shared_ptr<spdlog::logger> logger = nullptr);

  std::vector<std::string> parse_new_url(std::string body);

private:
  std::shared_ptr<spdlog::logger> logger;
  CDocument doc;
};

} // namespace Arachne
