#include <Hephaestus/Egutils.h>

TextProcessor::TextProcessor()
    : jieba(JIEBADICT_ROOT + std::string("jieba.dict.utf8"),
            JIEBADICT_ROOT + "hmm_model.utf8",
            JIEBADICT_ROOT + "user.dict.utf8", JIEBADICT_ROOT + "idf.utf8",
            JIEBADICT_ROOT + "stop_words.utf8") {}

std::set<std::string>
TextProcessor::getIntersection(std::string const &left,
                               std::string const &right) const {
  std::function<std::set<std::string>(std::string const &str)>
      from_string_to_set = [this](std::string const &str) {
        std::vector<std::string> vec;
        this->jieba.Cut(str, vec);
        // std::cout << str << ": ";
        // for(auto i : vec) {
        //     std::cout << i << " ";
        // }
        // std::cout << std::endl;
        return std::set<std::string>(std::make_move_iterator(vec.begin()),
                                     std::make_move_iterator(vec.end()));
      };

  auto set_left = from_string_to_set(left);
  auto set_right = from_string_to_set(right);
  std::set<std::string> result;
  std::set_intersection(set_left.begin(), set_left.end(), set_right.begin(),
                        set_right.end(),
                        // std::back_inserter(result)
                        std::inserter(result, result.begin()));
  return result;
}

std::string TextProcessor::strip(std::string const &str) const {
  auto start = str.find_first_not_of(" \n\t\r");
  if (start == std::string::npos) {
    return "";
  }
  auto end = str.find_last_not_of(" \n\t\r");
  return str.substr(start, end - start + 1);
}

std::string TextProcessor::process(std::string const &text) const {
  return strip(text);
}

std::string TextProcessor::setToString(std::set<std::string> const &s) const {
  std::string ret{};
  for (auto const &str : s) {
    ret += str + " ";
  }
  return ret;
}

// & > |
// "nihoa" | "helo" & "and" | "hllo" |"hello" &
std::string TextProcessor::advancedProcess(std::string const &text) const {
  using namespace std;
  std::stack<std::string> stk;
  std::string ret{};
  std::string stripedText{strip(text)};
  std::string ops{"|&"};
  auto begin{0};
  auto end{stripedText.find_first_of(ops, begin)};
  auto next_begin{0};
  auto next_end{0};
  auto str{strip(stripedText.substr(begin, end - begin))};

  stk.push(str);
  while (end != string::npos) {
    auto op = stripedText.substr(end, 1);
    next_begin = end + 1;
    next_end = stripedText.find_first_of(ops, next_begin);
    // 以运算符结尾时，运算符的右侧会由于无法找到子串而为
    // ""，这满足计算公式，因此无需额外考虑
    auto right{strip(stripedText.substr(next_begin, next_end - next_begin))};
    if (op == "|") {
      stk.push(right);
    } else if (op == "&") {
      auto left = stk.top();
      stk.pop();
      auto ret_set = getIntersection(left, right);
      auto result = setToString(ret_set);
      stk.push(result);
    } else {
      throw std::runtime_error("未知高级运算符");
    }
    begin = next_begin;
    end = next_end;
  }
  // preprocess
  while (!stk.empty()) {
    ret += stk.top() + " ";
    stk.pop();
  }
  return ret;
}

std::string CharUtils::wideToUtf8(wchar_t wideChar) const {
  std::string utf8Str;
  if (wideChar <= 0x7F) {
    // 单字节字符
    utf8Str.push_back(static_cast<char>(wideChar));
  } else if (wideChar <= 0x7FF) {
    // 两字节字符
    utf8Str.push_back(0xC0 | (wideChar >> 6));
    utf8Str.push_back(0x80 | (wideChar & 0x3F));
  } else if (wideChar <= 0xFFFF) {
    // 三字节字符
    utf8Str.push_back(0xE0 | (wideChar >> 12));
    utf8Str.push_back(0x80 | ((wideChar >> 6) & 0x3F));
    utf8Str.push_back(0x80 | (wideChar & 0x3F));
  } else if (wideChar <= 0x10FFFF) {
    // 四字节字符
    utf8Str.push_back(0xF0 | (wideChar >> 18));
    utf8Str.push_back(0x80 | ((wideChar >> 12) & 0x3F));
    utf8Str.push_back(0x80 | ((wideChar >> 6) & 0x3F));
    utf8Str.push_back(0x80 | (wideChar & 0x3F));
  }
  return utf8Str;
}

void CharUtils::extractChar(std::set<std::string> &s,
                            std::wstring const &charSet) const {
  // 遍历宽字符集
  for (auto const &c : charSet) {
    // 将宽字符转换为 UTF-8 编码的字符串
    std::string str_char = wideToUtf8(c);
    s.erase(str_char); // 删除字符
  }
}
