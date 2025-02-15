#include <Hephaestus/Cutter.h>
#include <Hephaestus/Includes.h>
#include <Hephaestus/InvIndex.h>
#include <grpcpp/grpcpp.h>
#include <include/addNew.grpc.pb.h>

class NewsOperator final : public NewsOperate::Service {
public:
  NewsOperator(Cutter &cutter, InvIndex &inv)
      : Service(), cutter(cutter), inv(inv) {}

  grpc::Status addNews(grpc::ServerContext *context, NewInfo const *request,
                       ResultResponse *response) override {
    using namespace grpc;
    std::vector<std::string> vec(7);
    vec.push_back(request->title());
    vec.push_back(request->author_photor());
    vec.push_back(request->referring());
    vec.push_back(request->source());
    vec.push_back(request->editor());
    vec.push_back(request->content());
    std::set<std::string> words;
    for (auto const &elem : vec) {
      auto temp = cutter.normalDivorce(elem);
      words.insert(std::move_iterator(temp.begin()),
                   std::move_iterator(temp.end()));
    }
    DocWordsWithId content{std::vector<std::string>(words.begin(), words.end()),
                           request->doc_id()};
    auto result = inv.putBatch(content);

    if (!result) {
      LOG_S("向数据库中添加索引时出错");
      response->set_result(Result::RESULT_FAILED);
      return Status(StatusCode::FAILED_PRECONDITION,
                    "向数据库中添加数据时失败");
    }
    response->set_result(Result::RESULT_SUCCESS);
    return Status::OK;
  }

private:
  Cutter &cutter;
  InvIndex &inv;
};
