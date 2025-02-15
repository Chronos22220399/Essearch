#pragma once
#include <Hephaestus/Includes.h>
#include <cppjieba/Jieba.hpp>

#define LOG()                                                                  \
  fmt::print("[{}:{}] {}\n",                                                   \
             (std::string(__FILE__).substr(                                    \
                 std::string(__FILE__).find("Engine/src"))),                   \
             __LINE__, __FUNCTION__)

#define LOG_S(message)                                                         \
  fmt::println(                                                                \
      "[{}, {}, {}, {}]\n",                                                    \
      std::string(__FILE__).substr(std::string(__FILE__).find("Engine/")),     \
      __LINE__, __FUNCTION__, message)
/*
校验
*/
template <typename T, typename = void> struct has_hash : std::false_type {};

template <typename T>
struct has_hash<T, std::void_t<decltype(std::hash<T>{}(std::declval<T>()))>>
    : std::true_type {};

template <typename Container, typename = void>
struct has_find : std::false_type {};

template <typename Container>
struct has_find<Container, std::void_t<decltype(std::declval<Container>().find(
                               std::declval<typename Container::key_type>()))>>
    : std::true_type {};

template <typename Container, typename = void>
struct is_iterable : std::false_type {};

template <typename Container>
struct is_iterable<Container,
                   std::void_t<decltype(std::begin(std::declval<Container>()),
                                        std::end(std::declval<Container>()))>>
    : std::true_type {};

template <typename Cutter, typename = void>
struct has_divorce : std::false_type {};

template <typename Cutter>
struct has_divorce<Cutter,
                   std::void_t<decltype(std::declval<Cutter>().normalDivorce(
                       std::declval<const std::string &>()))>>
    : std::true_type {};

template <typename Container, typename = void>
struct has_splice : std::false_type {};

template <typename Container>
struct has_splice<
    Container,
    std::void_t<decltype(std::declval<Container>().splice(
        std::declval<typename Container::iterator>(), std::declval<Container>(),
        std::declval<typename Container::iterator>()))>> : std::true_type {};

template <typename T> inline constexpr bool has_hash_v = has_hash<T>::value;

template <typename Container>
inline constexpr bool has_find_v = has_find<Container>::value;

template <typename Container>
inline constexpr bool is_iterable_v = is_iterable<Container>::value;

template <typename Container>
inline constexpr bool has_splice_v = has_splice<Container>::value;

template <typename Cutter>
inline constexpr bool has_divorce_v = has_divorce<Cutter>::value;
/*
校验
*/

/*
 打印容器内容
*/
template <typename T> inline auto display(T const &t) {
  fmt::print("{}", "{ ");
  for (auto &elem : t) {
    fmt::print("{} ", elem);
  }
  fmt::print("{}", "}\n");
}

/*
检测 optional 容器
*/
template <typename T> inline void optionalCheck(std::optional<T> const &elem) {
  if (!elem) {
    fmt::print("出现错误");
  }
  if (!elem.has_value()) {
    fmt::print("获得空值");
  }
}

struct TextProcessor {
public:
  TextProcessor();

  std::set<std::string> getIntersection(std::string const &left,
                                        std::string const &right) const;

  std::string strip(std::string const &str) const;

  std::string process(std::string const &text) const;

  std::string advancedProcess(std::string const &text) const;

  std::string setToString(std::set<std::string> const &s) const;

private:
  cppjieba::Jieba const jieba;
};

struct CharUtils {
  void extractChar(std::set<std::string> &s,
                   std::wstring const &charSet =
                       L" ,,.\"\'`~!/\\<•>-=()_@#$%^*。，《》（）-——；：'"
                       "{}「」,“”【】～·！？、，") const;

  std::string wideToUtf8(wchar_t wideChar) const;
};

/*
检查并根据情况更改当前工作路径
*/
inline void changeWorkSpace() {
  char cwd[1024];
  if ((getcwd(cwd, sizeof(cwd))) != nullptr) {
    auto s_cwd = std::string(cwd);
    fmt::print("当前工作路径: {}\n", s_cwd);
    if (s_cwd.substr(s_cwd.find_last_of("/"), -1) == "/build") {
      fmt::print("正在更改工作路径...\n");
      chdir("../");
    }
  }
}

/***********************************************/
// 已废弃
namespace old {

template <typename T, template <typename> class Checker> struct UniChecker {
  template <typename U>
  static auto test(int)
      -> decltype(Checker<U>::check(std::declval<U>()), std::true_type{});
  template <typename> static std::false_type test(...);

  static constexpr bool value = decltype(test<T>(0))::value;
};

template <typename T> struct has_hash {
  static auto check(T) -> decltype(std::hash<T>{}(std::declval<T>()));
};

template <typename Container> struct has_find {
  static auto check(Container) -> decltype(std::declval<Container>().find(
      std::declval<typename Container::key_type>()));
};

template <typename Container> struct is_iterable {
  static auto check(Container)
      -> decltype(std::begin(std::declval<Container>()),
                  std::end(std::declval<Container>()));
};

template <typename T, template <typename> class Checker>
inline constexpr bool unicheck_v = UniChecker<T, Checker>::value;

template <typename T>
inline constexpr bool has_hash_v = unicheck_v<T, has_hash>;

template <typename Container>
inline constexpr bool has_find_v = unicheck_v<Container, has_find>;

template <typename Container>
inline constexpr bool is_iterable_v = unicheck_v<Container, is_iterable>;

/*
        倒排索引的缓存
*/
// using size_type = size_t;

// struct InvCache {
// 	std::map<std::string, std::set<size_type>> cache;
// 	// Set capacity of lines
// 	std::optional<size_type> resize(size_type capacity);
// 	// Initialize the cache, return the inserted elem count
// 	std::optional<size_type> initialize(size_type capacity);
// 	// Insert value when running(runtime)
// 	std::optional<size_type> insert(DocWordsWithId const &doc);
// 	// Get doc id set by single word when running
// 	std::optional<std::set<size_type>> get(std::string const &word);
// 	// Get doc id lists by words list when running
// 	std::optional<std::set<size_type>>
// 	getWords(std::set<std::string> words);

// 	// Display to debug
// 	void display() {
// 		for (auto const &key: cache) {
// 			std::cout << key.first << " : ";
// 			for (auto const &elem: key.second) {
// 				std::cout << elem << std::endl;
// 			}
// 		}
// 	}

// 	// Get the instance of cache
// 	static inline InvCache &getCache() {
// 		static InvCache instance{};
// 		return instance;
// 	}

// 	InvCache(InvCache const &) = delete;
// 	InvCache &operator=(InvCache const &) = delete;

// private:
// 	InvCache() = default;
// 	size_t capacity;
// 	size_t size;
// };

// /*
// 倒排索引缓存开始
// */
// // 设置缓存容量
// // 返回正数，说明容量减小，负数说明容量增大
// std::optional<InvIndex::size_type> InvIndex::InvCache::resize(size_type
// capacity) {
//     this->capacity = capacity;
//     size_type ori_size = size;
//     auto& cache = getCache().cache;
//     // 默认删除尾部元素
//     while(size >= capacity) {
//         auto it = cache.end();
//         cache.erase(--it);
//     }
//     return { ori_size - capacity + 1 };
// }

// // Initialize the cache, return the inserted elem count
// std::optional<InvIndex::size_type> InvIndex::InvCache::initialize(size_type
// capacity = 10000) {
//     this->capacity = capacity;
//     this->size = 0;
//     // insert data from InvIndex
//     auto& inv = InvIndex::getInv();
//     auto result = inv.getInvIndexNCnt(capacity);
//     if (!(result and result.has_value())) {
//         LOG();
//         return std::nullopt;
//     }
//     this->size = result.value().size();
//     this->cache.insert(std::move_iterator(result.value().begin()),
//     std::move_iterator(result.value().end())); return { size };
// }

// // Insert value when running(runtime)
// std::optional<InvIndex::size_type> InvIndex::InvCache::insert(DocWordsWithId
// const& doc) {
//     size_type doc_id = doc.id;
//     for (auto const& word : doc.doc_words) {
//         auto result = cache[word].insert(doc_id);
//         if (not result.second) {
//             LOG();
//             return std::nullopt;
//         }
//     }
//     return { doc.doc_words.size() };
// }

// // Get doc id set by single word when running
// // firstly search the cache
// // secondly search the InvIndex
// std::optional<std::set<InvIndex::size_type>>
// InvIndex::InvCache::get(std::string const& word) {
//     // firstly search the cache
//     auto it = cache.find(word);
//     // find out
//     if (it == cache.end()) {
//         auto result = getInv().getSingle(word);
//         if (!result) {
//             return std::nullopt;
//         }
//         // 在倒排索引中找到了
//         // 将单词添加到缓存中
//         if (size >= capacity) {
//             LOG();
//             auto result = resize(capacity/10);
//             size = result.value();
//             fmt::print("缓存容量到达上限，现已删除 {} 条缓存", size);
//         }
//         cache[word] = result.value();
//         size++;
//         return { result.value() };
//     }
//     return { it->second };
// }

// // Get doc id lists by words list when running
// std::optional<std::set<InvIndex::size_type>>
// InvIndex::InvCache::getWords(std::set<std::string> words) {
//     std::set<size_type> retSet;
//     for (auto const& word : words) {
//         auto result = get(word);
//         if (result.has_value()) {
//             retSet.insert(std::move_iterator(result.value().begin()),
//             std::move_iterator(result.value().end()));
//         }
//     }
//     if (retSet.empty()) {
//         return std::nullopt;
//     }
//         return { retSet };
//     }
/*
倒排索引缓存结束
*/
} // namespace old
