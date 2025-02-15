#pragma once
#include <Hephaestus/Cache.hpp>
#include <Hephaestus/InvIndex.h>
#include <grpcpp/grpcpp.h>
#include <include/query.grpc.pb.h>

template <typename Key, typename Value,
          typename Container = std::list<Node<Key, Value>>>
using ListLRUCache = LRUCache<Key, Value, Container>;

using size_type = uint32_t;
using InvNode = Node<std::string, std::set<size_type>>;

// MARK: 还需要完成上锁相关的内容，具体在 cache.hpp 中
class InvLRUCache final : public ListLRUCache<std::string, std::set<size_type>,
                                              std::list<InvNode>> {
public:
  InvLRUCache(InvIndex &inv) : inv(inv) {}

  ~InvLRUCache() = default;

  auto doNotFoundKey(std::string const &key)
      -> std::optional<std::set<size_type>> override {
    auto result = inv.getSingle(key);
    if (!result) {
      LOG_S("缓存从数据库获取数据时出错");
      return std::nullopt;
    }
    if (!result.value().empty()) {
      LOG_S("值不为空，现在将数据从数据库存入缓存");
      this->put(key, result.value());
    }
    return result;
  }

private:
  InvIndex &inv;
};

template <typename Cutter> class Search final : public QueryProcessor::Service {
  static_assert(has_divorce_v<Cutter>, "Server 需要类型 Cutter");

public:
  explicit Search(Cutter &cutter, InvLRUCache &invCache)
      : QueryProcessor::Service(), cutter(cutter), invCache(invCache) {}

  grpc::Status QueryDocId(grpc::ServerContext *context,
                          QueryRequest const *request,
                          QueryResponse *response) override {
    using namespace grpc;
    QueryMode queryMode = request->querymode();
    std::string queryContent = request->querycontent();

    std::cout << "type: " << queryMode << std::endl;
    fmt::print("content: {}\n", queryContent);
    auto words = Divorce(queryMode, queryContent);
    // 查询模式错误，但 WebServer
    // 在传入前已对模式进行过检查，因此应该为传输过程中的错误
    if (!words) {
      LOG_S("查询出现错误");
      return Status(StatusCode::INVALID_ARGUMENT, "不合法的查询模式");
    }
    // 查询缓存
    std::set<size_type> doc_ids;
    for (auto &word : words.value()) {
      std::optional<std::set<size_type>> res = invCache.get(word);
      if (!res) {
        continue;
      }
      for (auto &id : res.value()) {
        doc_ids.insert(id);
      }
    }
    response->mutable_docid()->Assign(doc_ids.begin(), doc_ids.end());
    return Status::OK;
  }

  auto Divorce(QueryMode queryMode, std::string const &queryContent)
      -> std::optional<std::set<std::string>> {
    std::set<std::string> result;
    if (queryMode == QueryMode::Normal) {
      result = cutter.normalDivorce(queryContent);
    } else if (queryMode == QueryMode::Advanced) {
      result = cutter.advancedDivorce(queryContent);
    } else {
      return std::nullopt;
    }
    return {result};
  }

private:
  Cutter &cutter;
  InvLRUCache &invCache;
};
