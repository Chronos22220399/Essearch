#pragma once
#include <Arachne/Autils.hpp>
#include <Document.h>
#include <Node.h>
#include <string>
#include <tuple>

namespace Arachne {

class NewParser {

public:
private:
  using get_result = std::tuple<std::string, size_t>;

  std::string get_title();

  get_result get_info(const std::string &info,
                      const std::string &search_content,
                      const size_t &end) const;

  std::string get_content();

  std::string get_editor();

public:
  struct New {
    size_t newId;
    std::string title;
    std::string authorPhotor;
    std::string referring;
    std::string source;
    size_t clickedCnt;
    std::string content;
    std::string editor;
    std::string url;
  };

  NewParser() {}

  New parse(std::string html_body, const std::string &url);

private:
  CDocument doc;
};

} // namespace Arachne
