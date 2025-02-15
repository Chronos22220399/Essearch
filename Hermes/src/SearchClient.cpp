#include <Hermes/SearchClient.h>

// TODO: 待完成
crow::response SearchClient::search(const crow::request &req) {
  crow::json::rvalue data = crow::json::load(req.body);
  crow::response res;
  std::string token = data["token"].s();
  if (token == "") {
    return crow::response(404);
  }

  auto new_ids = query_hephaestus(data);
  auto request = std::make_unique<GetNewsRequest>();
  // 交换更高效
  request->mutable_docids()->Swap(new_ids->mutable_docids());
  auto news = query_arachne(std::move(request));

  return crow::response();
}

// finished
std::unique_ptr<SearchResponse>
SearchClient::query_hephaestus(crow::json::rvalue &data) {
  auto stub = SearchStubGetter::getStub("localhost:12321");

  SearchRequest request;
  SearchResponse response;
  grpc::ClientContext context;

  std::string search_mode = data["search_mode"].s();

  // 根据模式进行选择
  if (search_mode == "normal") {
    request.set_mode(SearchMode::Normal);
  } else if (search_mode == "advanced") {
    request.set_mode(SearchMode::Advanced);
  }

  request.set_content(data["search_mode"].s());
  stub->Search(&context, request, &response);

  return std::make_unique<SearchResponse>(response);
}

std::unique_ptr<GetNewsResponse>
SearchClient::query_arachne(std::unique_ptr<GetNewsRequest> request) {
  auto stub = SearchStubGetter::getStub("localhost:12321");
  return {};
}
