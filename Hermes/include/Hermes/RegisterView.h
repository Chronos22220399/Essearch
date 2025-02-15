#include <Hermes/Sqlite3.h>
#include <crow.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/spdlog.h>
#include <string>

class RegisterView final {
private:
  std::shared_ptr<spdlog::logger> logger;
  std::unique_ptr<Hermes::Sqlite3> admin_db;

public:
  RegisterView(std::shared_ptr<spdlog::logger> regLogger = nullptr);

  crow::response regist(const crow::request &req);

private:
  crow::response handle(const std::string &username,
                        const std::string &password,
                        crow::json::wvalue &res_data);

  bool password_is_valid(const std::string &password);

  void store_userinfo(const std::string &username,
                      const std::string &hashed_password);
};
