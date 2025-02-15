#include <Hephaestus/Cutter.h>

Cutter::Cutter()
    : jieba(JIEBADICT_ROOT + std::string("jieba.dict.utf8"),
            JIEBADICT_ROOT + "hmm_model.utf8",
            JIEBADICT_ROOT + "user.dict.utf8", JIEBADICT_ROOT + "idf.utf8",
            JIEBADICT_ROOT + "stop_words.utf8") {}

std::set<std::string> Cutter::normalDivorce(std::string const &text) const {
  std::vector<std::string> words;
  std::set<std::string> result{};
  jieba.CutForSearch(text, words, true);
  result.insert(std::move_iterator(words.begin()),
                std::move_iterator(words.end()));
  char_utils.extractChar(result);
  return result;
}

std::set<std::string> Cutter::advancedDivorce(std::string const &text) const {
  std::vector<std::string> words;
  std::set<std::string> result{};
  std::string sentence = text_processor.advancedProcess(text);
  jieba.CutForSearch(sentence, words);
  result.insert(std::move_iterator(words.begin()),
                std::move_iterator(words.end()));
  char_utils.extractChar(result);
  return result;
}

template <typename T>
using has_value_type = std::void_t<typename T::value_type>;

template <typename T, typename = void> struct HasValueType : std::false_type {};

template <typename T>
struct HasValueType<T, has_value_type<T>> : std::true_type {};

struct WithVT {
  using value_type = int;
};

struct WithoutVT {};
