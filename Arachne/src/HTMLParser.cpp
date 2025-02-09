#include <Arachne/HTMLParser.h>
#include <spdlog/sinks/base_sink.h>

namespace Arachne {

// 将url修正：从 https://news.hbut.edu.cn/xxxw/91.htm 获取的大部分 url
// 会是类似 ../info/1011/20310.htm 的形式，因此要将 .. 删去
void HTMLParser::amend_url(std::string &url) {
  if (url.starts_with("..")) {
    url = url.substr(2);
  }
  if (url.starts_with("http")) {
    url = "";
  }
  if (!url.starts_with("/")) {
    url = "/" + url;
  }
}

HTMLParser::HTMLParser(std::shared_ptr<spdlog::logger> logger)
    : logger(logger) {
  if (!logger) {
    CATCH_LOG("未对 logger 进行初始化");
    exit(-1);
  }
};

std::vector<std::string> HTMLParser::parse_new_url(std::string body) {
  std::vector<std::string> ret;
  doc.parse(body);
  CSelection c = doc.find("a.item.flex.p_r.flex-align-center");
  // 依次获取匹配到的链接
  for (size_t index = 0; index < c.nodeNum(); ++index) {
    std::string url = c.nodeAt(index).attribute("href");
    if (!url.empty()) {
      amend_url(url);
      fmt::println("成功添加url: {}", url);
      if (!url.empty()) {
        ret.push_back(url);
      }
    }
  }
  return ret;
}

} // namespace Arachne
