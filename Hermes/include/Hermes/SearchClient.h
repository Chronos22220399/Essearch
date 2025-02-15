#pragma once
#include <crow.h>
#include <grpc++/grpc++.h>
#include <grpcpp/client_context.h>
#include <grpcpp/security/credentials.h>
#include <include/search.grpc.pb.h>
#include <memory>
#include <nlohmann/json.hpp>
#include <spdlog/sinks/daily_file_sink.h>
#include <sqlpp11/sqlite3/sqlite3.h>

struct SearchStubGetter {
  static std::unique_ptr<SearchService::Stub>
  getStub(const std::string &address) {
    auto channel =
        grpc::CreateChannel(address, grpc::InsecureChannelCredentials());
    std::unique_ptr<SearchService::Stub> stub = SearchService::NewStub(channel);
    return stub;
  }
};

class SearchClient {
private:
  std::shared_ptr<spdlog::logger> logger;
  // std::unique_ptr<sqlpp::sqlite3::connection> db_ptr;

public:
  SearchClient(std::shared_ptr<spdlog::logger> logger) : logger(logger) {}

  crow::response search(const crow::request &req);

private:
  std::unique_ptr<SearchResponse> query_hephaestus(crow::json::rvalue &data);
  std::unique_ptr<GetNewsResponse>
  query_arachne(std::unique_ptr<GetNewsRequest> request);
};
