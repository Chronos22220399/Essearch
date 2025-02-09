#pragma once
#include <Arachne/URLGetter.h>
#include <Arachne/Utils.h>
#include <Document.h>
#include <News.h>
#include <Node.h>
#include <httplib.h>
#include <optional>
#include <sqlpp11/sqlite3/connection.h> // 如果是 SQLite3 数据库
#include <sqlpp11/sqlite3/sqlite3.h>
#include <sqlpp11/sqlpp11.h>

namespace Arachne {

class ContentParser {

public:
  std::optional<std::string> get_body(const std::string &url) {
    if (url.empty()) {
      logger->warn("url 为空");
      fmt::println("url 为空");
      return std::nullopt;
    }
    httplib::Client cli(domain);

    fmt::println("当前爬取链接: {}", domain + url);
    auto res = cli.Get(url);
    check_http_result(res, logger);
    std::string body = res->body;
    return {body};
  }

  std::optional<News::New> resolve_news(const std::string &url) {
    if (!get_body(url)) {
      return {};
    }

    News::New news{};
    std::string new_content{};
    CDocument doc;
    std::optional<std::string> body = get_body(url);
    if (!body) {
      logger->error("解析新闻失败");
      return std::nullopt;
    }

    // 解析html体
    doc.parse(body.value());
    // 解析新闻信息: title, author_photor, ...
    CNode info = doc.find("").nodeAt(0);

    // 解析 content
    CNode content = doc.find("div.v_news_content").nodeAt(0);
    CSelection paragraph = content.find("p");
    // 存储 content 部分
    for (size_t i = 0; i < paragraph.nodeNum(); ++i) {
      CNode node = paragraph.nodeAt(i);
      if (node.find("img").nodeNum()) {
        new_content += "\r\n" + node.find("img").nodeAt(0).attribute("src");
      } else {
        new_content += node.text();
      }
    }
    news.content = new_content;
    return news;
  }

  std::string get_content() {
    std::string new_content{};
    // content = doc.find("div.v_news_content").nodeAt(0);
  }

  ContentParser(std::shared_ptr<spdlog::logger> logger = nullptr)
      : logger(logger) {
    if (!logger) {
      CATCH_LOG("未对 logger 进行初始化");
      exit(-1);
    }
  }

private:
  std::shared_ptr<spdlog::logger> logger;
  const std::string domain = "https://news.hbut.edu.cn";
};

} // namespace Arachne
