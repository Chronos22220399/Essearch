#pragma once
// 容器
#include <optional>
#include <vector>
#include <list>
#include <stack>
#include <set>
#include <string>
#include <cstring>
#include <functional>
#include <map>
#include <unordered_map>
#include <queue>
// 多线程
#include <mutex>
#include <thread>
#include <future>
#include <condition_variable>
// 工具
#include <unistd.h>
#include <memory>
#include <chrono>
#include <iostream>
#include <type_traits>
#include <algorithm>
// 第三方
#include "fmt/format.h"

inline const std::string JIEBADICT_ROOT = "./thirdparty/cppjieba/dict/";
/* namespace std { */
/*  */
/* template <typename T, typename = const char*> */
/* struct __printer_test_c_str { */
/*     using type = void; */
/* }; */
/*  */
/* template <typename T> */
/* struct __printer_test_c_str<T, decltype(std::declval<T>().c_str())> {}; */
/*  */
/* template <typename T, int = 0, int = 0, int = 0, */
/*         typename = decltype(std::declval<std::ostream &>() << *++std::declval<T>().begin()),  */
/*         typename = decltype(std::declval<T>().begin() != std::declval<T>().end()), */
/*         typename = typename __printer_test_c_str<T>::type> */
/* std::ostream &operator<<(std::ostream &os, T const &v) { */
/*     os << '{'; */
/*     auto it = v.begin(); */
/*     if (it != v.end()) { */
/*         os << *it; */
/*         for (++it; it != v.end(); ++it) { */
/*             os << ',' << *it; */
/*         } */
/*     } */
/*     os << "}"; */
/*     return os; */
/* } */
/*  */
/* } */

