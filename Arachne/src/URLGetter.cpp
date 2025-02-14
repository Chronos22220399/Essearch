#include <Arachne/Autils.hpp>
#include <Arachne/URLGetter.h>
#include <httplib.h>

namespace Arachne {

// 将url修正：从 https://news.hbut.edu.cn/xxxw/91.htm 获取的大部分 url
// 会是类似 ../info/1011/20310.htm 的形式，因此要将 .. 删去
auto URLGetter::URLGetterParser::amend_url(const std::string &url) {
  if (url.size() < 8) {
    return static_cast<std::string>("");
  } else if (url.starts_with("..")) {
    return url.substr(2);
  } else if (url.starts_with("http") || !url.ends_with(".htm")) {
    return static_cast<std::string>("");
  } else if (!url.starts_with("/")) {
    return "/" + url;
  } else {
    return static_cast<std::string>("");
  }
}

std::vector<std::string>
URLGetter::URLGetterParser::parse_new_url(std::string body) {
  if (body.empty()) {
    LOG("请求结果的 body 为空");
    return {};
  }
  std::vector<std::string> ret;

  doc.parse(body);
  CSelection c = doc.find("a.item.flex.p_r.flex-align-center");
  // 依次获取匹配到的链接
  if (c.nodeNum() == 0) {
    LOG("未能解析到链接");
  } else {
    for (size_t index = 0; index < c.nodeNum(); ++index) {
      std::string url = c.nodeAt(index).attribute("href");
      if (!url.empty()) {
        url = amend_url(url);
        if (!url.empty()) {
          LOG("成功添加url: {}", url);
          ret.push_back(url);
        } else {
          LOG("修正后的 URL 为空");
        }
      } else {
        LOG("原始 URL 为空");
      }
    }
  }
  return ret;
}

// URLGetter::URLGetter(std::shared_ptr<spdlog::logger> logger)
//     : parser(), logger(logger) {
//   if (!logger) {
//     LOG("{}", "未对 logger 进行初始化");
//     exit(-1);
//   }
// };
URLGetter::URLGetter() {};

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
void URLGetter::get_new_urls(std::vector<std::string> &urls) {
  auto links = get_all_page_links();
  const size_t Cnt = 8;
  try {
    std::vector<std::thread> pool;
    std::vector<std::vector<std::string>> urls_content(Cnt);

    const size_t num = (links.size() + Cnt - 1) / Cnt;
    for (size_t i = 0; i < Cnt; ++i) {
      size_t start = i * num;
      size_t end = std::min((i + 1) * num, links.size());

      pool.emplace_back([start, end, i, &urls_content, &links, this]() mutable {
        httplib::Client cli(domain);
        URLGetterParser parser{};
        while (start < end) {
          if (start >= links.size()) {
            break; // 避免越界访问
          }

          assert(start < links.size());
          LOG("开始访问: {}", links[start]);

          auto res = cli.Get(links[start]);
          LOG("结束访问: {}", links[start]);

          if (!res) {
            LOG("{}", "res结果为空");
            exit(-1);
          }

          assert(res);
          if (res->status != 200) {
            LOG("获取回应出错: {}", res->status);
            continue;
          }
          std::string body = res->body;
          auto new_urls = parser.parse_new_url(body);
          urls_content[i].insert(urls_content[i].end(), new_urls.begin(),
                                 new_urls.end());
          start += 1;
        }
      });
    }
    for (auto &thread : pool) {
      thread.join();
    }
    for (size_t i = 0; i < urls_content.size(); ++i) {
      urls.insert(urls.end(), urls_content[i].begin(), urls_content[i].end());
    }
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

} // namespace Arachne
