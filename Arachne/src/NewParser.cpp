#include <Arachne/NewParser.h>

namespace Arachne {

using get_result = std::tuple<std::string, size_t>;

std::string NewParser::get_title() {
  return Autils::strip(doc.find("h1.te_c").nodeAt(0).text());
}

get_result NewParser::get_info(const std::string &info,
                               const std::string &search_content,
                               const size_t &end) const {
  size_t begin = info.find(search_content, end) + 3;
  size_t c_end = info.find(" ", begin);
  auto checker = info.substr(begin, c_end - begin);
  return {Autils::strip(checker), c_end};
}

std::string NewParser::get_content() {
  auto content = doc.find("div.v_news_content").find("p");
  std::string content_items{};
  for (size_t i = 0; i < content.nodeNum(); ++i) {
    auto node = content.nodeAt(i);
    // 图片
    auto imgs = node.find("img");
    if (imgs.nodeNum()) {
      for (size_t j = 0; j < imgs.nodeNum(); ++j) {
        content_items += "\r\n" + imgs.nodeAt(j).attribute("src");
      }
    } else { // 非图片
      content_items += (i == 0 ? "" : "\r\n") + node.text();
    }
  }
  return Autils::strip(content_items);
}

std::string NewParser::get_editor() {
  auto editor = doc.find("div.edit").nodeAt(0).text();
  size_t begin = editor.find("：") + 3;
  size_t end = editor.find(" ", begin);
  editor = editor.substr(begin, end - begin);
  return Autils::strip(editor);
}

NewParser::New NewParser::parse(std::string html_body, const std::string &url) {
  doc.parse(html_body);
  auto title = get_title();
  fmt::println("{}", title);
  auto new_info = Autils::strip(doc.find("div.info.te_c div").nodeAt(0).text());

  // 获取作者/摄影
  auto author_photor = get_info(new_info, "：", 0);
  LOG("{}", std::get<0>(author_photor));

  // 获取审稿
  auto checker = get_info(new_info, "：", std::get<1>(author_photor));
  LOG("{}", std::get<0>(checker));

  // 获取出处
  auto source = get_info(new_info, "：", std::get<1>(checker));
  LOG("{}", std::get<0>(source));

  // 获取内容
  auto content = get_content();
  LOG("{}", content);

  // 获取编辑
  auto editor = get_editor();
  LOG("{}", editor);

  return New{.newId = 0,
             .title = title,
             .authorPhotor = std::get<0>(author_photor),
             .referring = std::get<0>(checker),
             .source = std::get<0>(source),
             .clickedCnt = 0,
             .content = content,
             .editor = editor,
             .url = url};
}

} // namespace Arachne
