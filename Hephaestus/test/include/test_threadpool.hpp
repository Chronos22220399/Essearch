#pragma once
#include <Hephaestus/Cutter.h>
#include <Hephaestus/ThreadPool.hpp>

inline void segment(Cutter const &cutter, std::string const &sentence,
                    std::promise<std::set<std::string>> resultPromise) {
  auto result = cutter.normalDivorce(sentence);
  resultPromise.set_value(result);
}

inline void test_threadpool(Cutter &cutter) {
  ThreadPool pool{4};
  std::vector<std::string> sentences = {
      "cppjieba是一个非常高效的中文分词库",
      "它支持多线程和高性能的分词需求",
      "在多线程环境中可以安全地使用",
      "使用cppjieba可以轻松实现高性能分词",
  };

  std::vector<std::future<std::set<std::string>>> results;
  for (const auto &sentence : sentences) {
    std::promise<std::set<std::string>> resultPromise;
    results.push_back(resultPromise.get_future());
    pool.enqueue([&, resultPromise = std::move(resultPromise)]() mutable {
      segment(cutter, sentence, std::move(resultPromise));
      return false;
    });
  }

  for (auto &result : results) {
    std::set<std::string> words = result.get();
    for (const auto &word : words) {
      std::cout << word << " ";
    }
    std::cout << std::endl;
  }
}
