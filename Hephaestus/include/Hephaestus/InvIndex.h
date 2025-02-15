#pragma once
#include <Hephaestus/Egutils.h>
#include <Hephaestus/Includes.h>
#include <fmt/format.h>
#include <leveldb/db.h>
#include <leveldb/write_batch.h>

struct DocWordsWithId {
private:
  using size_type = uint32_t;

public:
  DocWordsWithId() = default;

  DocWordsWithId(std::vector<std::string> const &words, size_type id)
      : doc_words(words), id(id) {}

  std::vector<std::string> doc_words;
  size_type id;
};

class InvIndex {
  using size_type = uint32_t;
  // std::string erase_password = "Essearch123456";
  std::string erase_password = "";

public:
  ~InvIndex();

  InvIndex(std::string const &db_name = "Inv",
           bool const &create_if_missing = true);

  // 将一篇文档中的词语批量存入倒排索引
  std::optional<size_type> putBatch(DocWordsWithId const &doc);

  // 将单个词语存入倒排索引
  std::optional<size_type>
  putSingle(std::pair<std::string, size_type> const &single_word);

  // 通过单个词语获取文档列表
  std::optional<std::set<size_type>> getSingle(std::string const &word);

  // 通过词语获取一系列文档列表, 由于是通过 words 中的 word
  // 获取，因此不使用迭代器
  std::optional<std::map<std::string, std::set<size_type>>>
  getByWords(std::set<std::string> const &words);

  // 获取前 n 个索引
  std::optional<std::map<std::string, std::set<size_type>>>
  getInvIndexNCnt(size_type const &count);

  // 查看前 n 条内容
  void displayNth(size_type n = -1);

  // 清空索引
  void eraseAll();

  InvIndex(InvIndex const &) = delete;

  InvIndex &operator=(InvIndex const &) = delete;

private:
  std::string serialize(std::set<size_type> const &vec);

  std::string serialize(size_type const &id);

  std::set<size_type> deserialize(std::string binary);

  template <typename T>
  std::optional<T> checkStatus(leveldb::Status &status, T const &result) {
    if (status.IsNotFound()) {
      fmt::println("未能找到: {}", status.ToString(), __FILE__);
      return std::nullopt;
    } else if (!status.ok()) {
      fmt::println("{}", status.ToString(), __FILE__);
      return std::nullopt;
    }
    return std::optional{result};
  }

public:
  static inline InvIndex &getInstance() {
    static InvIndex instance{};
    return instance;
  }

  size_type size;
  leveldb::DB *db = nullptr;
  std::string const ROOT_PATH = "/home/Ess/Code/Project/Essearch/Engine/Datas/";
};
