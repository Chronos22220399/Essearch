#pragma once
#include <Hephaestus/Cutter.h>
#include <Hephaestus/Includes.h>
#include <Hephaestus/InvIndex.h>
#include <Hephaestus/Search.hpp>

// inline static Cutter cutter{};
// inline static std::vector<std::string> words;

inline void test(Cutter const &cutter, std::string const &text) {
  auto start = std::chrono::high_resolution_clock::now();
  cutter.advancedDivorce(text);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
  // std::cout << limonp::Join(words.begin(), words.end(), " ") << std::endl;
  std::cout << "耗时: " << duration.count() << std::endl;
}

void test_1() {
  std::string text{
      R"(分配设备：用户输入作业名、设备类名和相对号。系统检查设备类表，若有空闲设备，则从设备表中选择符合条件的设备并分配给作业，更新设备类表和设备表中的状态。
	•	回收设备：用户输入作业名和设备类名，系统查找设备表中的作业名，释放设备并更新状态，设备类表中的“现存好的设备”数增加。)"};
  Cutter cutter{};
  // std::vector<std::string> words;
  auto words = cutter.advancedDivorce(text);
  std::cout << words << std::endl;
}

void test_inv_index() {
  // DocWordsWithId did({"hello", "湖北工业大学"}, 2);
  // InvIndex::getInstance().putBatch(std::move(did));
  // InvIndex::getInstance().putSingle({"再也", 2});
  // auto result = InvIndex::getInstance().getSingle("s");
  // auto result = InvIndex::getInstance().getByWords({"s", "hello"});
  // if (not result.has_value()) {
  // 	fmt::print("元素不存在\n");
  // 	return;
  // }
  // for (auto &id : result.value()) {
  // 	std::cout << id << std::endl;
  // }
  InvIndex::getInstance().displayNth();
  // InvIndex::getInstance().eraseAll();
}

void test_cache() {
  InvIndex inv;
  InvLRUCache cache(inv);
  cache.put("hello", {1});
  auto result = cache.get("hello");
  optionalCheck(result);

  for (auto const id : result.value()) {
    fmt::print("{} ", id);
  }
  fmt::print("\n");
}

void test_server() {
  changeWorkSpace();
  InvIndex inv;
  InvLRUCache cache(inv);
  Cutter cutter{};
  Search server(cutter, cache);
  server.Divorce(QueryMode::Normal, "hello");
}
